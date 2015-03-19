#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>
#include "ipc.h"

#define PORT 5156
#define MAX_BACKLOG 5
#define MES_Q_IDENT (key_t)0x4A
#define SHMEM_IDENT (key_t)0xE2
#define SHMEM_SIZE	1024

int main(int argc, char *argv[])
{
	int sd, client_sd;
	struct sockaddr_in server, client;
	int client_len = sizeof(client);

	int msq_id = openMessageQueue(MES_Q_IDENT);
	int shmem_id;
	void *shmem_p = openSharedMemory(SHMEM_IDENT, SHMEM_SIZE, &shmem_id);
	
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
	closeSharedMemory(shmem_id);
	closeMessageQueue(msq_id);
	return 0;
}
