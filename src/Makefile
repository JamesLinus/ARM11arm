CC      = gcc
CFLAGS  = -fPIC -pie -g -std=c99 -Werror -pedantic
BIN=../bin/
OBJ=../obj
RES=./res
UTILS=./utilities/

PROG=emulate assemble
MODS=decode.o errorDump.o execute.o binaryLoading.o 
OS=$(addprefix $(OBJ)/, $(MODS))
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST) $(OS)

clean:
	rm $(LIST)
	rm $(OS)

$(BIN)/assemble: assemble.c assemble.h
	$(CC) -o $(BIN)/assemble $(CFLAGS) assemble.c

$(BIN)/emulate: emulate.c emulate.h $(OS)
	$(CC) $(CFLAGS) -o $(BIN)/emulate emulate.c $(OS)

$(OBJ)/%.o: $(UTILS)/%.c $(UTILS)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<
