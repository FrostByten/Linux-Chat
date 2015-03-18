#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>

#define PORT 5156
#define MAX_BACKLOG 5

int main(int argc, char *argv[])
{
	int sd, client_sd;
	struct sockaddr_in server, client;
	int client_len = sizeof(client);
	
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Can't create socket");
		exit(1);
	}
	
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't bind socket");
		exit(1);
	}
	
	listen(sd, MAX_BACKLOG);
	printf("Server listening on port %d\n", PORT);
	
	for(;;)
	{
		if((client_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1)
		{
			perror("Can't accept client");
			exit(1);
		}
		
		printf("\tConnection from: %s\n", inet_ntoa(client.sin_addr));
		close(client_sd);		
	}
	
	close(sd);
	return 0;
}
