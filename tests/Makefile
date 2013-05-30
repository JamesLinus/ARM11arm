CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

TESTSRC = $(wildcard *.c)
PROGSRC = $(wildcard ../src/*.c)

all: $(PROGSRC)

test:
	all

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
