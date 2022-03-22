CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -m

.PHONY: all clean

all: tsp

tsp: tsp.o graph.o stack.o path.o
	$(CC) -o tsp tsp.o graph.o stack.o path.o $(FLAGS)

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c 
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

format: 
	clang-format -i -style=file *.c *.h

clean: 
	rm *.o tsp

scan-build: clean
	scan-build make

