CC=gcc

all: server.o
	$(CC) -o server server.o
server.o:
	$(CC) -c server.c -o server.o
clean:
	rm -f *.o *.out core.* server
