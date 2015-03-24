#include "network.h"

int efd;
client_entry clients[MAX_CLIENTS];
short current = 0;
struct epoll_event event;
struct epoll_event *events;

void startAccept(int sd)
{
	set_sock_noblock(sd);

	if((efd = epoll_create1(0)) == -1)
	{
		perror("Unable to create epoll fd");
		exit(1);
	}

	event.data.fd = sd;
	event.events = EPOLLIN | EPOLLET;
	if(epoll_ctl(efd, EPOLL_CTL_ADD, sd, &event) == -1)
		perror("Unable to add listen socket event to epoll fd");

	events = calloc(MAX_EVENTS, sizeof(event));

	for(;;)
	{
		int i;
		int n = epoll_wait(efd, events, MAX_EVENTS, -1);

		for(i = 0; i < n; ++i)
		{
			if(events[i].data.fd == sd) // New connection!
				accept_client(i, sd);
			else // Data to be read!
			{
				if(read_from_client(i))
				{
					client_disconnect(i);
					break;
				}
			}
		}
	}

	free(events);
	close(sd);
	close(efd);

	int k;
	for(k = 0; k < current; ++k)
	{
		if(clients[k].fd != 0)
			close(clients[k].fd);
		if(clients[k].nick != NULL)
			free(clients[k].nick);
	}
}

void set_sock_noblock(int sd)
{
	int flags = fcntl(sd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(sd, F_SETFL, flags);
}

void accept_client(int i, int sd)
{
	struct sockaddr_in client;
	int client_len = sizeof(client);
	int client_sd;

	if((client_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1)
		perror("Can't accept client");
	else
	{
		int l;
		for(l = 0; l < current; ++l)
		{
			send_message(clients[current].fd, CHAT, "Some guy connected", strlen("Some guy connected"));
		}

		clients[current].nick = NULL;
		clients[current].fd = client_sd;
		set_sock_noblock(client_sd);
		memcpy(&(clients[current].addr), &client, client_len);

		event.data.fd = client_sd;
		event.events = EPOLLIN | EPOLLET;
		if(epoll_ctl(efd, EPOLL_CTL_ADD, client_sd, &event) == -1)
			perror("Cannot add client to epoll watch list");

		syslog(LOG_INFO, "Connection from: %s\n", inet_ntoa(client.sin_addr));
		printf("Connection from: %s\n", inet_ntoa(clients[current].addr.sin_addr));

		current++;
	}
}

void client_disconnect(int i)
{
	int j;
	for(j = 0; j < current; ++j)
	{
		if(clients[j].fd == events[i].data.fd)
		{
			printf("%s disconnected", inet_ntoa(clients[j].addr.sin_addr));
			clients[j].fd = 0;
			if(clients[j].nick != NULL)
				free(clients[j].nick);
		}
		else
		{
			send_message(clients[current].fd, CHAT, "Some guy disconnected", strlen("Some guy disconnected"));
		}
	}
	close(events[i].data.fd);
}

int read_from_client(int i)
{
	int count;
	char buffer[READ_BUFF_SIZE];

	count = read(events[i].data.fd, buffer, sizeof(buffer));
	if(count == -1)
	{
		if(errno != EAGAIN) //Error reading, disconnect
		{
			perror("Reading from client");
			return 1;
		}
	}
	else if(count == 0) // Connection closed
		return 1;
	else
		handle_message(events[i].data.fd, buffer, count);

	return 0;
}

void send_message(int fd, char type, char *data, int length)
{
	char *buf = (char*)malloc(length+1);
	buf[0] = type;

	memcpy(&buf[1], data, length);
	send(fd, buf, length+1, 0);
	free(buf);
}

void handle_message(int fd, char* buf, int len)
{
	char type = buf[0];
	char d; // Index of client received from

	for(d = 0; d < current; ++d)
		if(clients[d].fd == fd)
			buf[0] = d;

	switch(type)
	{
		case CHAT:
		{
			for(d = 0; d < current; ++d)
			{
				if(clients[d].fd != fd)
					send_message(clients[d].fd, CHAT, buf, len);
			}

			printf("[%s]: %s\n", clients[buf[0]].nick==NULL?inet_ntoa(clients[buf[0]].addr.sin_addr):clients[buf[0]].nick, buf+1);
			break;
		}
		case NAME_CHANGE:
		{
			printf("[%s]: Changed name to: %s\n", clients[buf[0]].nick==NULL?inet_ntoa(clients[buf[0]].addr.sin_addr):clients[buf[0]].nick, buf+1);

			if(clients[d].nick != NULL)
				free(clients[d].nick);

			clients[d].nick = (char*)malloc(len-1);
				memcpy(clients[d].nick, buf + 1, len - 1);

			for(d = 0; d < current; ++d)
			{
				if(clients[d].fd != fd)
					send_message(clients[d].fd, NAME_CHANGE, buf, len);
			}

			break;
		}
		default:
			break;
	}
}
