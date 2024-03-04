CC = gcc
CFLAGS = -Wall

.PHONY: clean

all:
	$(CC) $(CFLAGS) src/main.c

clean:
	rm a.out