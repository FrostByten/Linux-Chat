CC=gcc

all: daemon.o
	$(CC) -o daemon daemon.o
daemon.o:
	$(CC) -c daemon.c -o daemon.o
clean:
	rm -f *.o *.out core.* daemon
