	#include <stdlib.h>
	#include <stdio.h>
	#include "../include/drive.h"
	#include "hardware.h"
	#include <assert.h>
	#include <string.h>

	static void empty_it() {
		return;
	}

	int main(int argc, char** argv) {
		int i,j;

		/* init hardware */
		if(init_hardware("hardware.ini") == 0) {
			fprintf(stderr, "Error in hardware initialization\n");
			exit(EXIT_FAILURE);
		}

		/* Interreupt handlers */
		for(i=0; i<16; i++)
			IRQVECTOR[i] = empty_it;

		/* Allows all IT */
		_mask(1);


		if ( argv[1] != NULL && strcmp(argv[1], "-reverse" ) == 0 ){

		for ( i = HDA_MAXCYLINDER - 1; i >= 0 ; i-- ){
			for ( j = HDA_MAXSECTOR - 1; j >= 0 ; j-- ){
				format_sector(i, j, 0x00000000);
			}
		}


		}else{

		
		for ( i = 0 ; i < HDA_MAXCYLINDER ; i++ ){
			for ( j = 0 ; j < HDA_MAXSECTOR ; j++ ){
				format_sector(i, j, 0x00000000);
			}
		}

		}


		return EXIT_SUCCESS;
	}
