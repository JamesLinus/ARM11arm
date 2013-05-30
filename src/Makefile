CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
BIN=../bin/

PROG=assemble emulate
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST)

clean: $(LIST)
	rm $(LIST)
	rm -rf $(BIN)/*.dSYM

$(BIN)/%:  %.c
	$(CC) $< $(CFLAGS) -o $@