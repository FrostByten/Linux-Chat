CC=gcc

all: client.o
	$(CC) -o client client.o
client.o:
	$(CC) -c client.c -o client.o
clean:
	rm -f *.o *.out core.* client
