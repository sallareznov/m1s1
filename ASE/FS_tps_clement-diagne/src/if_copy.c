
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "../include/ifile.h"
#include "hardware.h"


#define LINE_SIZE 4096

static void empty_it(){
  return;
}


int main(int argc, char const *argv[])
{
	unsigned int i;
	unsigned int inumber;
	char line[LINE_SIZE];
	struct file_desc_t fd;

	if (argc < 2) {
		printf("Usage : if_copy [inumber] -> ecrit le contenu de l'entrée standard dans l'inode de numero [inumber]\n");
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

  	open_ifile(&fd, inumber, 0);

	
	while (fgets(line, LINE_SIZE, stdin) != NULL) {
	  
	  write_ifile(&fd, line, strlen(line), 0);
   
	}



  	close_ifile(&fd, 0);

  	return EXIT_SUCCESS;
}
