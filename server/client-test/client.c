#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/prctl.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <strings.h>

#define PORT 5156
#define BUFLEN 80

void runChild(int);
void sigHandler(int);

pid_t pid;

int main(int argc, char *argv[])
{
	pid = getpid();
	int sd, port;
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[BUFLEN];
	
	if(argc < 2)
	{
		printf("Usage: %s [ip address] {port}\n", argv[0]);
		exit(1);
	}

	port = argc==3?atoi(argv[2]):PORT;

	
	if(signal(SIGINT, sigHandler) == SIG_ERR)
	{
		perror("Can't set signal handler");
		exit(1);
	}
	
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Can't create socket");
		exit(1);
	}
	
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(argv[1]);
	
	if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't connect to server");
		exit(1);
	}
	printf("Connected to: %s:%d\n", argv[1], port);
	
	pid_t t = fork();
	if(t == 0) // Child will receive
	{
		runChild(sd);
		exit(0);
	}
	
	// Parent will send
	pid = t;
	for(;;)
	{
		printf("Transmit: ");
		fgets(buf, BUFLEN, stdin);
		if(send(sd, buf, BUFLEN, 0) == -1)
		{
			printf("Connection severed...\n");
			fflush(stdout);
			close(sd);
			getchar();
			return 0;
		}
	}
	
	fflush(stdout);
	close(sd);
	return 0;
}

void runChild(int fd)
{
	char buf[BUFLEN];
	int n;

	prctl(PR_SET_PDEATHSIG, SIGHUP);
	
	for(;;)
	{
		n = 0;
		while((n = recv(fd, buf + n, BUFLEN - n, 0)) < BUFLEN);
		
		printf("Received: %s\nTransmit: ", buf);
		fflush(stdout);
	}
}

void sigHandler(int signo)
{
	if(signo == SIGINT)
	{
		printf("\nCaught interrupt signal, dying...\n");
		kill(pid, SIGKILL);
		exit(1);
	}
}
