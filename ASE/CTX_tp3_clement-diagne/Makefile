CC		= gcc
CFLAGS	= -c -Wall -Werror -m32 -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g
CFLAGS += -I/home/enseign/ASE/include

all: pingpongpang sem_example

ctx_s.o: ctx_s.c
	$(CC) $(CFLAGS) -c ctx_s.c -o ctx_s.o

sem_s.o: sem_s.c 
	$(CC) $(CFLAGS) sem_s.c -o sem_s.o 

pingpongpang: pingpongpang.o ctx_s.o 
	$(CC) pingpongpang.o ctx_s.o -o pingpongpang -L/home/enseign/ASE/lib -I/home/enseign/ASE/include -lhardware

pingpongpang.o: pingpongpang.c pingpongpang.h ctx_s.h
	$(CC) $(CFLAGS) pingpongpang.c -o pingpongpang.o 


sem_example: sem_example.o ctx_s.o sem_s.o
	$(CC) sem_example.c ctx_s.o sem_s.o -o sem_example -L/home/enseign/ASE/lib -I/home/enseign/ASE/include -lhardware

sem_example.o: sem_example.c ctx_s.h sem_s.h
	$(CC) $(CFLAGS) sem_example.c -o sem_example.o 

.PHONY: clean realclean

clean:
	$(RM) ctx_s.o sem_s.o pingpongpang.o sem_example.o

realclean:
	$(RM) pingpongpang sem_example