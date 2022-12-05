CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra -gdwarf-4 $(shell pkg-config --cflags gmp)
LFLAGS   = $(shell pkg-config --libs gmp)

encode: encode.c code.o huffman.o io.o node.o pq.o stack.o
		$(CC) -o $@ $^

decode: decode.o code.o huffman.o io.o node.o pq.o stack.o
		$(CC) -o $@ $^


all: encode decode


%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

spotless:
	rm -f encode decode *.o

format:
	clang-format -i -style=file decode.c code.c huffman.c io.c node.c pq.c stack.c
