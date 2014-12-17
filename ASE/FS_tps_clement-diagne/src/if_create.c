
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/ifile.h"
#include "hardware.h"


static void empty_it(){
  return;
}

int main(int argc, char** argv){
	unsigned int i;
	enum inode_type_e type;

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

  	type = REG_FILE;

  	printf("File N.%d created\n", create_ifile(type, 0));
	return EXIT_SUCCESS;



}



