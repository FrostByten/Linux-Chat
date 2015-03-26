CC=gcc

all: server.o
	$(CC) -o server server.o network.o
server.o: network.o
	$(CC) -c server.c -o server.o
network.o:
	$(CC) -c network.c -o network.o
clean:
	rm -f *.o *.out core.* server
