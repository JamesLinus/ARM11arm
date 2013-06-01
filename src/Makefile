CC      = gcc
CFLAGS  = -pid -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
BIN=../bin/

PROG=emulate
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST)

clean: $(LIST)
	rm $(LIST)

$(BIN)/assemble: assemble.c
	$(CC) -o $(BIN)/assemble $(CFLAGS) assemble.c

$(BIN)/emulate: emulate.c
	$(CC) -o $(BIN)/emulate $(CFLAGS) emulate.c