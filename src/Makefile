CC      = gcc
CFLAGS  = -pie -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
BIN=../bin/

PROG=emulate assemble
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST)

clean: $(LIST)
	rm $(LIST)

$(BIN)/assemble: assemble.c assemble.h
	$(CC) -o $(BIN)/assemble $(CFLAGS) assemble.c

$(BIN)/emulate: emulate.c emulate.h
	$(CC) -o $(BIN)/emulate $(CFLAGS) emulate.c