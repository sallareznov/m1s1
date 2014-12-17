
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/ifile.h"
#include "hardware.h"

static void empty_it(){
  return;
}


int main(int argc, char const *argv[])
{
	unsigned int i;
	unsigned int inumber;

	if (argc < 2) {
		printf("Usage : if_delete [inumber] -> supprimer l'inode de numero [inumber] et renvoi OK ou KO\n");
		return EXIT_FAILURE;
	}

  /* init hardware */
  if(init_hardware("hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  /* Interreupt handlers */
  for(i=0; i<16; i++) {
    IRQVECTOR[i] = empty_it;
  }

  /* Allows all IT */
  _mask(1);

  printf("Loading Master Boot Record...\n");
  load_mbr();

  	load_super(0);

  	inumber = atoi(argv[1]);

  	delete_ifile(inumber, 0);

  	return EXIT_SUCCESS;
}