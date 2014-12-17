/* main de mkvol */

#include "../include/vol.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

static void empty_it(){
  return;
}


int main(int argc, char** argv){
  unsigned int i;

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


  if ( argc < 2 ){
    printf("Usage : rmvol volume_number\n");
    return EXIT_FAILURE;
  }



  /* /!\ verifier qu'il n'y a pas deja 8 volumes present /!\ */


   printf("Loading Master Boot Record...\n");
  load_mbr();

  if ( mbr.n_vol <= atoi(argv[1]) ){
    printf("Hard drive does not contain volumes n°%d.\n", atoi(argv[1]));
    return EXIT_FAILURE;
  }

  printf("Deleting volume %d...\n", atoi(argv[1]));

  for ( i = atoi(argv[1]) ;  i < MAX_VOL-1 ; i++ ){
    mbr.vol[i] = mbr.vol[i+1];
  }
  mbr.n_vol--;



  save_mbr();

  printf("Volume %d deleted.\n", atoi(argv[1]));
  return EXIT_SUCCESS;
}