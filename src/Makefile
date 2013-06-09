CC      = gcc
CFLAGS  = -pie -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
BIN=../bin/
OBJ=../obj/

PROG=emulate assemble
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST)

clean:
	rm $(LIST)

$(BIN)/assemble: assemble.c assemble.h
	$(CC) -o $(BIN)/assemble $(CFLAGS) assemble.c

$(BIN)/emulate: emulate.c utilities/binaryLoading.c utilities/decode.c utilities/execute.c
	$(CC) -o $(BIN)/emulate $(CFLAGS) emulate.c utilities/binaryLoading.c utilities/decode.c utilities/execute.c utilities/errorDump.c
