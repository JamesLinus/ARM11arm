CC      = gcc
CFLAGS  = -fPIC -pie -g -std=c99 -Werror -pedantic
BIN=../bin/
OBJ=../obj
RES=./res
UTILS=./utilities/

PROG=emulate assemble
# Emulate modules /////////////////////////////////////////
EMODS=decode.o errorDump.o execute.o binaryLoading.o
EOS=$(addprefix $(OBJ)/, $(EMODS))
# Assembly modules ////////////////////////////////////////
AMODS=functionAssemble.o
AOS=$(addprefix $(OBJ)/, $(AMODS))
# All modules /////////////////////////////////////////////
MODS= $(EMODS) $(AMODS)
OS=$(addprefix $(OBJ)/, $(MODS))

AOS=$(addprefix $(OBJ)/, $(AMODS))

LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST) $(OS)

clean:
	rm $(LIST)
	rm $(OS)

$(BIN)/assemble: assemble.c assemble.h
	$(CC) -o $(BIN)/assemble $(CFLAGS) assemble.c $(AOS)

$(BIN)/emulate: emulate.c emulate.h $(OS)
	$(CC) $(CFLAGS) -o $(BIN)/emulate emulate.c $(EOS)

$(OBJ)/%.o: $(UTILS)/%.c $(UTILS)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<
