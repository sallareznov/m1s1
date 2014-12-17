CC	= gcc
CFLAGS	= -Wall -ansi
CFLAGS += -g

HDR_DIR = include
SRC_DIR = src
OBJ_DIR = lib
BIN_DIR = bin

OBJECTS_FILES	= $(wildcard $(OBJ_DIR)/*.o)
BINARIES_FILES	= $(wildcard $(BIN_DIR)/*)
HIDDEN_FILES	= *~

COMPILED_OBJECTS	= mmu.o mi_user.o mi_kernel.o
COMPILED_BINARIES	= mi_kernel

all: $(COMPILED_OBJECTS) $(COMPILED_BINARIES)

mmu.o: $(SRC_DIR)/mmu.c $(HDR_DIR)/mmu.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mmu.c -o $(OBJ_DIR)/mmu.o -I $(HDR_DIR)

mi_user.o: $(SRC_DIR)/mi_user.c $(HDR_DIR)/mi_user.h $(OBJ_DIR)/mmu.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mi_user.c -o $(OBJ_DIR)/mi_user.o -I $(HDR_DIR)

mi_kernel.o: $(SRC_DIR)/mi_kernel.c $(OBJ_DIR)/mi_user.o
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mi_kernel.c -o $(OBJ_DIR)/mi_kernel.o -I $(HDR_DIR)

mi_kernel: $(OBJ_DIR)/mi_kernel.o
	$(CC) $(OBJ_DIR)/mmu.o $(OBJ_DIR)/mi_user.o $(OBJ_DIR)/mi_kernel.o -o $(BIN_DIR)/mi_kernel -L $(OBJ_DIR) -lhardware

.PHONY: clean mrproper

clean:
	$(RM) $(OBJECTS_FILES) $(BINARIES_FILES)

mrproper:
	$(RM) $(HIDDEN_FILES)

realclean: clean mrproper
