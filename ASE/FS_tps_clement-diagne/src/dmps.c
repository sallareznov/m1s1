#include <stdlib.h>
#include <stdio.h>
#include "../include/drive.h"
#include "hardware.h"
#include <assert.h>


static void empty_it(){
	return;
}

int main(int argc, char** argv){
	unsigned int i;
	int numeroCylinder;
	int numeroSector;
	unsigned char* buffer;

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


	assert(argc==3);
	numeroCylinder = atoi(argv[1]);
	numeroSector = atoi(argv[2]);
  
	buffer = malloc(sizeof(char)*HDA_SECTORSIZE);
	assert(buffer);

	read_sector(numeroCylinder, numeroSector, buffer);

	for ( i = 0 ; i < HDA_SECTORSIZE ; i++ ) {
		printf("%01X\n", buffer[i]);
	}

	free(buffer);
	return EXIT_SUCCESS;
}
