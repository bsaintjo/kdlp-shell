CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wcast-qual -Wconversion -Wdouble-promotion

# ifeq ($(CC), gcc)
# 	CFLAGS += -Wduplicated-branches -Wduplicated-cond
# endif

.PHONY: clean all shell test

all: shell

shell: args.o
	$(CC) $(CFLAGS) src/main.c src/args.o

test: CFLAGS += -g3 -gdwarf-2 -DDEBUG
test: args.o
	$(CC) $(CFLAGS) -o test/test test/test_args.c src/args.o
	./test/test

clean:
	rm a.out
	rm src/*.o
	rm test/test

args.o: src/args.c src/args.h
	$(CC) $(CFLAGS) -g -c src/args.c -o src/args.o
