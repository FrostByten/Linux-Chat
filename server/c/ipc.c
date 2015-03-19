#include "ipc.h"

int openMessageQueue(key_t ident)
{
	int msq_id;

	if((msq_id = msgget(ident, IPC_CREAT)) < 0)
	{
		perror("Can't open message queue");
		exit(1);
	}

	return msq_id;
}

void *openSharedMemory(key_t ident, int size, int *shmid)
{
	void *p = NULL;

	if((*shmid = shmget(ident, size, 0600 | IPC_CREAT | IPC_EXCL)) < 0)
	{
		perror("Can't open shared memory");
		exit(1);
	}

	if((p = (void*)shmat(*shmid, NULL, 0)) == (void*)-1)
	{
		perror("Can't attach shared memory");
		exit(1);
	}

	return p;
}

void closeMessageQueue(key_t ident)
{
	if(msgctl(ident, IPC_RMID, 0) < 0)
		perror("Can't close message queue");
}

void closeSharedMemory(int ident)
{
	if(shmctl(ident, IPC_RMID, (struct shmid_ds*)NULL) < 0)
		perror("Can't close shared memory");
} 
