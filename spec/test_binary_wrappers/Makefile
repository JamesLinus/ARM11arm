CC      = gcc
CFLAGS  = -pie -g -std=c99 -Werror -pedantic

all: maskTests

maskTests: maskTests.c
	$(CC) -o maskTests $(CFLAGS) maskTests.c
	rm -rf *.dSYM

