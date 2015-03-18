#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

#define NAME "Thowis_Scallentire_Chat"

void end(int, char*);

int main(int argc, char *argv[])
{
	pid_t pid;

	setlogmask(LOG_UPTO(LOG_ERR));
	openlog(NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
	
	syslog(LOG_INFO, "Starting...");
	
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
	
	end(0, NULL);
	return 0;
}

void end(int status, char *message)
{
	if(message != NULL)
		syslog(LOG_ERR, message);
	syslog(LOG_INFO, "Stopping...");
	
	closelog();
	exit(status);
}
