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

COMPILED_OBJECTS	= ctx_s.o pingpong.o
COMPILED_BINARIES	= pingpong

all: $(COMPILED_OBJECTS) $(COMPILED_BINARIES)

### OBJECTS ###

ctx_s.o: $(SRC_DIR)/ctx_s.c $(HDR_DIR)/ctx_s.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ctx_s.c -o $(OBJ_DIR)/ctx_s.o

pingpong.o: $(SRC_DIR)/pingpong.c $(HDR_DIR)/pingpong.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/pingpong.c -o $(OBJ_DIR)/pingpong.o

### BINARIES ###

pingpong: $(OBJ_DIR)/ctx_s.o $(OBJ_DIR)/pingpong.o
	$(CC) $(OBJ_DIR)/ctx_s.o $(OBJ_DIR)/pingpong.o -o $(BIN_DIR)/pingpong

### AFTER-USE ###

.PHONY: clean mrproper

clean:
	$(RM) $(OBJECTS_FILES)

mrproper:
	$(RM) $(BINARIES_FILES) $(HIDDEN_FILES)

realclean: clean mrproper
