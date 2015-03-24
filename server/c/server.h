#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <strings.h>
#include "shared.h"
#include "network.h"

#define PORT 5156
#define MAX_BACKLOG 5
#define MES_Q_IDENT (key_t)0x4A
#define SHMEM_IDENT (key_t)0xE2
#define MAX_CLIENTS 100

typedef struct client_entry
{
	struct sockaddr_in addr;
	char *nick;
	int fd;
} client_entry;

int main(int, char**);
void end(int, char*);
pid_t daemonize();
void startListen();

#endif
