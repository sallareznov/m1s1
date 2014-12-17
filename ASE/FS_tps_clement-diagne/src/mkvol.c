/* main de mkvol */

#include "../include/vol.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include <string.h>
#include <time.h>


static void empty_it(){
  return;
}


int main(int argc, char** argv){
  int v, first_cylinder, first_sector, n_block;
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


  if ( argc < 5 ){
    printf("Usage : mkvol vol_name first_cylinder first_sector nb_block [-tother, -tannexe]\n");
    return EXIT_FAILURE;
  }

  first_cylinder = atoi(argv[2]);
  first_sector = atoi(argv[3]);
  n_block = atoi(argv[4]);

  if ( atoi(argv[2])==0 && atoi(argv[3])==0 ){
    printf("Cannot create volume at Master Boot Record position.\n");
    return EXIT_FAILURE;
  }


   printf("Loading Master Boot Record...\n");
  load_mbr();

  if ( mbr.n_vol >= MAX_VOL ){
    printf("Hard drive already has 8 volumes, please delete at least one volume before creating new one.\n");
    return EXIT_FAILURE;
  }

  first_cylinder = atoi(argv[2]);

  check_before_create(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

  v = mbr.n_vol;
  mbr.vol[v].first_cylinder = first_cylinder;
  mbr.vol[v].first_sector = first_sector;
  mbr.vol[v].n_block = n_block;

  printf("Creating volume %d...\n", v);
  mbr.vol[v].type = BASE;
  if ( argc == 5 ){
    if ( strcmp(argv[4], "-tother") == 0){
      mbr.vol[v].type = OTHER;
    }
    if ( strcmp(argv[4], "-tannexe") == 0){
      mbr.vol[v].type = ANNEXE;
    }
  }


  srand((unsigned)time(NULL));
  init_super(v, argv[1], rand(), n_block);


  mbr.n_vol++;
  save_mbr();
  save_super(v);

  printf("Volume %d created.\n", v);
  return EXIT_SUCCESS;
}