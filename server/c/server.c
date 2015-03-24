#include "server.h"

//#define DAEMON

int sd, msq_id, shmem_id;

int main(int argc, char *argv[])
{
	#ifdef DAEMON
		pid_t sid = daemonize();
	#endif

	startListen();
	startAccept(sd);
	
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

void startListen()
{
	struct sockaddr_in server;

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		end(1, "Can't create listening socket!");
	
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
		end(1, "Can't bind listen socket!");
	
	listen(sd, MAX_BACKLOG);
	printf("Listening on port %d\n", PORT);
	syslog(LOG_INFO, "Listening on port %d", PORT);
}
