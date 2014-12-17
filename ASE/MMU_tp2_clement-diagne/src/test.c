#include <stdio.h>
#include <stdlib.h>
#include "../include/mmu.h"
#include "hardware.h"

static void mmuhandler() {
    printf("tentative d’accès illégal à l’adresse %d\n", _in(MMU_FAULT_ADDR));
    exit(EXIT_FAILURE);
}

static void empty_it(){
  return;
}

int main(int argc, char **argv) {
    char *ptr;
    int i;
    
    if(init_hardware("hardware.ini") == 0) {
    	fprintf(stderr, "Error in hardware initialization\n");
    	exit(EXIT_FAILURE);
  	}	

  	/* Interrupt handlers */
  	for(i=0; i<16; i++) {
    	IRQVECTOR[i] = empty_it;
  	}

    /* init_hardware() */
    IRQVECTOR[MMU_IRQ] = mmuhandler;
    _mask(1);

    ptr = (char*)0;
    *ptr = 'c';

    return EXIT_SUCCESS;
}
