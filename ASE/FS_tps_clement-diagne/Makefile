# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic 
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= bin/mkhd bin/frmt bin/dmps bin/mkvol bin/rmvol bin/dvol bin/if_create bin/if_delete bin/if_dump bin/if_copy
OBJECTS	= $(addsuffix .o,\
	  lib/mkhd lib/drive lib/vol lib/frmt lib/dmps lib/mkvol lib/rmvol lib/dvol lib/ifile lib/if_dump lib/if_copy lib/if_delete lib/if_create)

all: $(OBJECTS) $(BINARIES)


###------------------------------
### Main rules 
###------------------------------------------------------------
lib/mkhd.o: src/mkhd.c
	$(CC) $(CFLAGS) -c src/mkhd.c -o lib/mkhd.o $(INCDIR)

bin/mkhd: lib/mkhd.o
	$(CC) $(CFLAGS) -o bin/mkhd lib/mkhd.o $(LIBS)

lib/drive.o: src/drive.c
	$(CC) $(CFLAGS) -c src/drive.c -o lib/drive.o $(INCDIR)

lib/vol.o: src/vol.c
	$(CC) $(CFLAGS) -c src/vol.c -o lib/vol.o $(INCDIR)

lib/frmt.o: src/frmt.c
	$(CC) $(CFLAGS) -c src/frmt.c -o lib/frmt.o $(INCDIR)

bin/frmt: lib/frmt.o
	$(CC) $(CFLAGS) -o bin/frmt lib/frmt.o lib/drive.o $(LIBS)

lib/dmps.o: src/dmps.c
	$(CC) $(CFLAGS) -c src/dmps.c -o lib/dmps.o $(INCDIR)

bin/dmps: lib/dmps.o
	$(CC) $(CFLAGS) -o bin/dmps lib/dmps.o lib/drive.o $(LIBS)

lib/mkvol.o: src/mkvol.c
	$(CC) $(CFLAGS) -c src/mkvol.c -o lib/mkvol.o $(INCDIR)

bin/mkvol: lib/mkvol.o
	$(CC) $(CFLAGS) -o bin/mkvol lib/mkvol.o lib/drive.o lib/vol.o $(LIBS)

lib/rmvol.o: src/rmvol.c
	$(CC) $(CFLAGS) -c src/rmvol.c -o lib/rmvol.o $(INCDIR)

bin/rmvol: lib/rmvol.o
	$(CC) $(CFLAGS) -o bin/rmvol lib/rmvol.o lib/drive.o lib/vol.o $(LIBS)

lib/dvol.o: src/dvol.c
	$(CC) $(CFLAGS) -c src/dvol.c -o lib/dvol.o $(INCDIR)

bin/dvol: lib/dvol.o
	$(CC) $(CFLAGS) -o bin/dvol lib/dvol.o lib/drive.o lib/vol.o $(LIBS)

lib/ifile.o: src/ifile.c
	$(CC) $(CFLAGS) -c src/ifile.c -o lib/ifile.o $(INCDIR)

lib/if_create.o: src/if_create.c
	$(CC) $(CFLAGS) -c src/if_create.c -o lib/if_create.o $(INCDIR)

lib/if_dump.o: src/if_dump.c
	$(CC) $(CFLAGS) -c src/if_dump.c -o lib/if_dump.o $(INCDIR)

lib/if_copy.o: src/if_copy.c
	$(CC) $(CFLAGS) -c src/if_copy.c -o lib/if_copy.o $(INCDIR)

lib/if_delete.o: src/if_delete.c
	$(CC) $(CFLAGS) -c src/if_delete.c -o lib/if_delete.o $(INCDIR)

bin/if_create: lib/if_create.o lib/ifile.o 
	$(CC) $(CFLAGS) -o bin/if_create lib/if_create.o lib/ifile.o lib/drive.o lib/vol.o $(LIBS)

bin/if_dump: lib/if_dump.o lib/ifile.o
	$(CC) $(CFLAGS) -o bin/if_dump lib/if_dump.o lib/drive.o lib/ifile.o lib/vol.o $(LIBS)

bin/if_copy: lib/if_copy.o lib/ifile.o
	$(CC) $(CFLAGS) -o bin/if_copy lib/if_copy.o lib/drive.o lib/ifile.o lib/vol.o $(LIBS)

bin/if_delete: lib/if_delete.o lib/ifile.o
	$(CC) $(CFLAGS) -o bin/if_delete lib/if_delete.o lib/drive.o lib/ifile.o lib/vol.o $(LIBS)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES) $(OBJECTS) ~*
realclean: clean 
	$(RM) bin/vdiskA.bin bin/vdiskB.bin
