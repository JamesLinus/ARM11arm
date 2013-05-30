CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
BIN=../bin/

PROG=assemble emulate utilities arm
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST)

clean: $(LIST)
	rm $(LIST)

$(BIN)/%:  %.c
	$(CC) $(INC) $< $(CFLAGS) -o $@ $(LIBS)

$(BIN)/emulate: emulate.c utilities.c arm.c

$(BIN)/utilities: utilities.c
	$(CC) -c utilities.c -o $@

$(BIN)/arm: arm.c
	$(CC) -c arm.c -o $@