ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi
CFLAGS += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

HDR_DIR = include
SRC_DIR = src
OBJ_DIR = lib
BIN_DIR = bin

OBJECTS_FILES	= $(wildcard $(OBJ_DIR)/*.o)
BINARIES_FILES	= $(wildcard $(BIN_DIR)/*)
HIDDEN_FILES	= *~

COMPILED_OBJECTS	= test.o mmu.o mi_user.o mi_kernel.o swap.o
COMPILED_BINARIES	= test mi_kernel

all: $(COMPILED_OBJECTS) $(COMPILED_BINARIES)

test.o: $(SRC_DIR)/test.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/test.c -o $(OBJ_DIR)/test.o $(INCDIR)

mmu.o: $(SRC_DIR)/mmu.c $(HDR_DIR)/mmu.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mmu.c -o $(OBJ_DIR)/mmu.o $(INCDIR) 

mi_user.o: $(SRC_DIR)/mi_user.c $(HDR_DIR)/mi_user.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mi_user.c -o $(OBJ_DIR)/mi_user.o $(INCDIR)

mi_kernel.o: $(SRC_DIR)/mi_kernel.c $(HDR_DIR)/mi_syscall.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mi_kernel.c -o $(OBJ_DIR)/mi_kernel.o $(INCDIR)

swap.o: $(SRC_DIR)/swap.c $(HDR_DIR)/swap.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/swap.c -o $(OBJ_DIR)/swap.o $(INCDIR)

test: $(OBJ_DIR)/test.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/test.o -o $(BIN_DIR)/test $(LIBS)

mi_kernel: $(OBJ_DIR)/mi_kernel.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/mi_kernel.o $(OBJ_DIR)/mmu.o $(OBJ_DIR)/mi_user.o $(OBJ_DIR)/swap.o -o $(BIN_DIR)/mi_kernel $(LIBS)