CC		= gcc
CFLAGS	= -Wall -Werror -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g

all: clean realclean divide

divide.o: divide.c
	$(CC) $(CFLAGS) -c divide.c -o divide.o

divide: divide.o
	$(CC) $(CFLAGS) divide.o -o divide

.PHONY: clean realclean

clean:
	$(RM) divide.o

realclean:
	$(RM) divide