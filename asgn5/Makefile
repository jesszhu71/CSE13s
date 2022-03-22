CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

.PHONY: all clean

all: encode decode error entropy

encode: encode.o bm.o bv.o hamming.o nibble.o
	$(CC) -o encode encode.o bm.o bv.o hamming.o nibble.o

decode: decode.o bm.o bv.o hamming.o nibble.o
	$(CC) -o decode decode.o bm.o bv.o hamming.o nibble.o

error: error.o 
	$(CC) -o error error.o 

entropy: entropy.o
	$(CC) -o entropy entropy.o $(LFLAGS)




encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

bv.0: bv.c
	$(CC) $(CFLAGS) -c bv.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

error.o: error.c
	$(CC) $(CFLAGS) -c error.c

entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c

nibble.o: nibble.c
	$(CC) $(CFLAGS) -c nibble.c



format:
	clang-format -i -style=file *.c *.h

clean:
	rm *.o encode decode error entropy

scan-build: clean
	scan-build make
