#ifndef IPC_H
#define IPC_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int openMessageQueue(key_t);
void *openSharedMemory(key_t, int, int*);
void closeMessageQueue(key_t);
void closeSharedMemory(int);


#endif
