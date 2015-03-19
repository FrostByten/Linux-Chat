#include "server.h"

int sd, msq_id, shmem_id;

int main(int argc, char *argv[])
{
	int client_sd;
	struct sockaddr_in server, client;
	int client_len = sizeof(client);
	void *shmem_p;

	//pid_t sid = daemonize();

	shmem_p = openSharedMemory(SHMEM_IDENT, SHMEM_SIZE, &shmem_id);
	msq_id = openMessageQueue(MES_Q_IDENT);
	
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Can't create socket");
		end(1, "Can't create listening socket!");
	}
	
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't bind socket");
		end(1, "Can't bind listen socket!");
	}
	
	listen(sd, MAX_BACKLOG);
	printf("Listening on port %d\n", PORT);
	syslog(LOG_INFO, "Server listening on port %d", PORT);
	
	for(;;)
	{
		if((client_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1)
		{
			perror("Can't accept client");
			end(1, "Can't accept client connection!");
		}
		
		printf("\tConnection from: %s\n", inet_ntoa(client.sin_addr));
		close(client_sd);		
	}
	
	return 0;
}

void end(int status, char *message)
{
	if(message != NULL)
	{
		syslog(LOG_ERR, "%s: %m", message);
		printf("%s\n", message);
	}	
	syslog(LOG_NOTICE, "Stopping...");
	
	close(sd);
	closeSharedMemory(shmem_id);
	closeMessageQueue(msq_id);

	closelog();
	exit(status);
}

pid_t daemonize()
{
	pid_t pid;

	setlogmask(LOG_UPTO(LOG_CRIT));
	openlog(NULL, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
	syslog(LOG_NOTICE, "Starting...");
	
	pid = fork();
	
	if(pid < 0)
		end(1, "Unable to fork daemon process!");
	else if(pid > 0)
		exit(0);
	
	umask(0);
	pid = setsid();
	if(pid < 0)
		end(1, "Unable to set signature id!");
	
	if((chdir("/")) < 0)
		end(1, "Unable to change directories!");
	
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	return pid;
}
