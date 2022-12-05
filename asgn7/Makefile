CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra -gdwarf-4 $(shell pkg-config --cflags gmp)

all: encode decode

decode: decode.c code.o huffman.o io.o node.o pq.o stack.o
		$(CC) -o $@ $^

encode: encode.c code.o huffman.o io.o node.o pq.o stack.o
		$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode *.o

spotless:
	rm -f encode decode *.o

format:
	clang-format -i -style=file decode.c code.c huffman.c io.c node.c pq.c stack.c
