CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

.PHONY: all clean

all: sorting

sorting: sorting.o bubble.o shell.o quick.o stack.o queue.o set.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o stack.o queue.o set.o $(FLAGS)

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

format:
	clang-format -i -style=file *.c *.h
clean:
	rm *.o sorting

scan-build: clean
	scan-build make
