/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: network.c - Performs the network-specific functions for the server
--
-- PROGRAM: Thowis Scallentire Chat
--
-- FUNCTIONS:
-- void startAccept(int);
-- void set_sock_noblock(int);
-- void accept_client(int, int);
-- void client_disconnect(int);
-- int read_from_client(int);
-- void send_message(int, char, char*, int);
-- void handle_message(int, char*, int);
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
----------------------------------------------------------------------------------------------------------------------*/

#include "network.h"

int efd;
client_entry clients[MAX_CLIENTS];
short current = 0;
struct epoll_event event;
struct epoll_event *events;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startAccept
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: void startAccept(int sd)
--
-- PARAMETERS:	int sd:		The socket to accept on
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: set_sock_noblock
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: void set_sock_noblock(int sd)
--
-- PARAMETERS:	int sd: The socket to set no-block on
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
void set_sock_noblock(int sd)
{
	int flags = fcntl(sd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(sd, F_SETFL, flags);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: accept_client
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: void accept_client(int i, int sd);
--
-- PARAMETERS:	int i:	The current iteration through the main loop: The next client to be added
--				int sd:	The socket to accept from
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
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
			//send_message(clients[current].fd, CHAT, "Some guy connected", strlen("Some guy connected"));
			send_message(clients[current].fd, CONNECTION, inet_ntoa(client.sin_addr), strlen(inet_ntoa(client.sin_addr)));
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
		printf("[%s]: Connected\n", inet_ntoa(clients[current].addr.sin_addr));

		current++;
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: client_disconnect
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: client_disconnect(int i);
--
-- PARAMETERS:	int i: The current iteration through the client select loop
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
void client_disconnect(int i)
{
	int j;
	for(j = 0; j < current; ++j)
	{
		if(clients[j].fd == events[i].data.fd)
		{
			printf("[%s]: Disconnected", clients[j].nick==NULL?inet_ntoa(clients[j].addr.sin_addr):clients[j].nick);
			clients[j].fd = 0;
			if(clients[j].nick != NULL)
				free(clients[j].nick);
		}
		else
		{
			//send_message(clients[current].fd, CHAT, "Some guy disconnected", strlen("Some guy disconnected"));
			send_message(clients[current].fd, DISCONNECTION, "", 0);
		}
	}
	close(events[i].data.fd);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: read_from_client
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: int read_from_client(int i);
--
-- PARAMETERS:	int i: The index of the client to read from
--
-- RETURNS: int. Whether or not the client disconnected
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: send_message
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: void send_message(int fd, char type, char *data, int length);
--
-- PARAMETERS:	int fd:		The socket to send to
--				char type:	The type of message to send
--				char *data:	The data of the message
--				int length:	The length of the data
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
void send_message(int fd, char type, char *data, int length)
{
	char *buf = (char*)malloc(length+1);
	buf[0] = type;

	memcpy(&buf[1], data, length);

	if(fd != 0)
		send(fd, buf, length+1, 0);

	free(buf);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: handle_message
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: handle_message(int fd, char *buf, int len)
--
-- PARAMETERS:	int fd:		The socket the message came from
--				char *buf:	The message that was read
--				int len:	The length of the message
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
void handle_message(int fd, char *buf, int len)
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
