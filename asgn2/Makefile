CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

.PHONY: all clean

all: mathlib-test

mathlib-test: mathlib-test.o mathlib.o
	$(CC) -o mathlib-test mathlib-test.o mathlib.o $(LFLAGS)

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c

mathlib.o: mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c

clean:
	rm *.o mathlib-test

scan-build: clean
	scan-build make
