# This is a file that will allow the grader to type make to compile your program. You will have to
# make this yourself for this assignment. We will cover this in lecture on November 8. You are encouraged to
# refer to Makefiles from previous CSE13S assignments as examples of how to write your own.
# • CC=clang must be specified.
# • CFLAGS=-Wall -Wextra -Werror -Wpedantic must be included.
# • make should build the banhammer executable, as should make all.
# • make clean must remove all files that are compiler generated except the executable.
# • make spotless must remove all files that are compiler generated as well as the executable.
# • make format should format all your source code, including the header files.




# WE HAVE TO MAKE OUR OWN CODE FOR MAKEFILE !*(@*&#&*!!()!(@&(*&#)))

EXECBIN  = banhammer

SOURCES  = $(wildcard *.c)
OBJECTS  = $(SOURCES:%.c=%.o)

CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra -gdwarf-4 $(shell pkg-config --cflags gmp)
LFLAGS   = $(shell pkg-config --libs gmp)

.PHONY: all clean

all: $(EXECBIN)

$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJECTS) *.pdf
