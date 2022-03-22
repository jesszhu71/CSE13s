CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all clean

all: banhammer

banhammer: banhammer.o bf.o bv.o ht.o ll.o node.o parser.o speck.o
	$(CC) -o banhammer banhammer.o bf.o bv.o ht.o ll.o node.o parser.o speck.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

format: 
	clang-format -i -style=file *.c *.h

clean: 
	rm *.o banhammer

scan-build: clean
	scan-build make


