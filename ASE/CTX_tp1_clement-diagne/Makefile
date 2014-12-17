CC	= gcc
CFLAGS	= -Wall -Werror -pedantic -m32
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

HDR_DIR = include
SRC_DIR = src
OBJ_DIR = lib
BIN_DIR = bin

OBJECTS_FILES	= $(wildcard $(OBJ_DIR)/*.o)
BINARIES_FILES	= $(wildcard $(BIN_DIR)/*)
HIDDEN_FILES	= *~

COMPILED_OBJECTS	= display_stack.o try.o try_mul.o 
COMPILED_BINARIES	= display_stack try_mul

all: $(COMPILED_OBJECTS) $(COMPILED_BINARIES)

### OBJECTS ###

display_stack.o: $(SRC_DIR)/display_stack.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/display_stack.c -o $(OBJ_DIR)/display_stack.o

try.o: $(SRC_DIR)/try.c $(HDR_DIR)/try.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/try.c -o $(OBJ_DIR)/try.o -I $(HDR_DIR)

try_mul.o: $(SRC_DIR)/try_mul.c $(SRC_DIR)/try.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/try_mul.c -o $(OBJ_DIR)/try_mul.o

### BINARIES ###

display_stack: $(OBJ_DIR)/display_stack.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/display_stack.o -o $(BIN_DIR)/display_stack

try_mul: $(OBJ_DIR)/try_mul.o $(OBJ_DIR)/try.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/try_mul.o $(OBJ_DIR)/try.o -o $(BIN_DIR)/try_mul

### AFTER-USE ###

.PHONY: clean mrproper

clean:
	$(RM) $(OBJECTS_FILES)

mrproper:
	$(RM) $(BINARIES_FILES) $(HIDDEN_FILES)

realclean: clean mrproper
