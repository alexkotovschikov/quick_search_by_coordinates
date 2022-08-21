CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

all: run
	rm -rf *.o

run:
	$(CC) $(CFLAGS) main.c short.c -o ../build/run.exe

refill: refill.c
	$(CC) $(CFLAGS) refill.c short.c

clean:
	rm -rf *.o ../build/run.exe