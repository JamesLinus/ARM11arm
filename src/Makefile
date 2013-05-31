CC      = gcc
CFLAGS  = -pid -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
BIN=../bin/
OBJ=../objs/

PROG=emulate
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST)

clean: $(LIST)
	rm $(LIST)

$(BIN)/assemble: assemble.c assemble.h
	$(CC) -o $(BIN)/assemble $(CFLAGS) assemble.c assemble.h

$(BIN)/emulate: emulate.c emulate.h utilities.o
	$(CC) -o $(BIN)/emulate $(CFLAGS) emulate.c utilities.o

utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) -c utilities.c