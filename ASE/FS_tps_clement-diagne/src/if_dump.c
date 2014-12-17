
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
	unsigned char res;
	struct file_desc_t fd;

	if (argc < 2) {
		printf("Usage : if_dump [inumber] -> affiche le contenu du fichier d'inode de numero [inumber]\n");
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

	while((res=readc_ifile(&fd)) != IFILE_EOF)
	  printf("%c", res);


  	close_ifile(&fd, 0);

  	return EXIT_SUCCESS;
}
