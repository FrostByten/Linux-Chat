/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: server.c - Main function for the server
--
-- PROGRAM: Thowis Scallentire Chat
--
-- FUNCTIONS:
-- int main(int, char**);
-- void end(int, char*);
-- pid_t daemonize();
-- void startListen();
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
----------------------------------------------------------------------------------------------------------------------*/

#include "server.h"

//#define DAEMON

int sd, msq_id, shmem_id;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: main
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: int main(int argc, char *argv[])
--
-- PARAMETERS:	int argc:		The number of supplied arguments
--				char *argv[]:	The suppied arguments
--
-- RETURNS: int. Program return status
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	#ifdef DAEMON
		pid_t sid = daemonize();
	#endif

	startListen();
	startAccept(sd);
	
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: end
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: void end(int status, char *message)
--
-- PARAMETERS:	int status:		The status to return to the shell
--				char *message:	The error message to display, if any
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: daemonize
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: pid_t daemonize()
--
-- PARAMETERS:	void
--
-- RETURNS: pid_t. The session id of the daemon
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: startListen
--
-- DATE: March 24th, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Lewis Scott
--
-- PROGRAMMER: Lewis Scott
--
-- INTERFACE: void startListen()
--
-- PARAMETERS:	void
--
-- RETURNS: void.
--
-- NOTES:
----------------------------------------------------------------------------------------------------------------------*/
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
