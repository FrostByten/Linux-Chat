/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: network.h - Performs the network-specific functions for the server
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

#ifndef NETWORK_H
#define NETWORK_H

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/epoll.h>
#include "shared.h"
#include "server.h"

#define MAX_EVENTS 64
#define READ_BUFF_SIZE 512

void startAccept(int);
void set_sock_noblock(int);
void accept_client(int, int);
void client_disconnect(int);
int read_from_client(int);
void send_message(int, char, char*, int);
void handle_message(int, char*, int);

#endif 
