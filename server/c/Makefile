CC=gcc

all: server.o
	$(CC) -o server server.o ipc.o
server.o: ipc.o
	$(CC) -c server.c -o server.o
ipc.o:
	$(CC) -c ipc.c -o ipc.o
clean:
	rm -f *.o *.out core.* server
