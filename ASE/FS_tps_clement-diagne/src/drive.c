#include "../include/drive.h"
#include "hardware.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

void check(unsigned int cylinder, unsigned int sector) {
	assert(cylinder < HDA_MAXCYLINDER);
	assert(sector < HDA_MAXSECTOR);
}

void seek_sector(unsigned int cylinder, unsigned int sector) {
	unsigned int hs = (sector >> 8) & 0xFF;
	unsigned int ls = sector & 0xFF;
	unsigned int hc = (cylinder >> 8) & 0xFF;
	unsigned int lc = cylinder & 0xFF;

	_out(0x110, hc);
	_out(0x111, lc);
	_out(0x112, hs);
	_out(0x113, ls);

	check(cylinder, sector);

	_out(HDA_CMDREG, SEEK);
	_sleep(HDA_IRQ);
}

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer) {
	seek_sector(cylinder, sector);
	
	_out(0x110, 0);
	_out(0x111, 1);

	 check(cylinder, sector);
	
	_out(HDA_CMDREG, READ);
	_sleep(HDA_IRQ);

	memcpy(buffer, MASTERBUFFER, HDA_SECTORSIZE);

}

void read_n_sector(unsigned int cylinder, unsigned int sector, unsigned int size, unsigned char *buffer) {
	int i;
	seek_sector(cylinder, sector);
	
	_out(0x110, 0);
	_out(0x111, 1);

	check(cylinder, sector);
	
	_out(HDA_CMDREG, READ);
	_sleep(HDA_IRQ);


	assert(size<=HDA_SECTORSIZE);
	for (i = 0 ; i < size ; i++) {
		buffer[i] = MASTERBUFFER[i];
	}
}


void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer) {
	seek_sector(cylinder, sector);

	_out(0x110, 0);
	_out(0x111, 1);

	memcpy(MASTERBUFFER, buffer, HDA_SECTORSIZE);

	check(cylinder, sector);

	_out(HDA_CMDREG, WRITE);
	_sleep(HDA_IRQ);
}

void write_n_sector(unsigned int cylinder, unsigned int sector, unsigned int size, const unsigned char *buffer){
	int i;
	seek_sector(cylinder, sector);

	_out(0x110, 0);
	_out(0x111, 1);


	assert(size<=HDA_SECTORSIZE);
	for ( i = 0 ; i < size ; i++ ){
		MASTERBUFFER[i] = buffer[i];
	}


	check(cylinder, sector);

	_out(HDA_CMDREG, WRITE);
	_sleep(HDA_IRQ);	
}

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value) {
	seek_sector(cylinder, sector);
	
	_out(0x110, 0);
	_out(0x111, 1);
	_out(0x112, (value >> 24) & 0xFF);
	_out(0x113, (value >> 16) & 0xFF);
	_out(0x114, (value >> 8) & 0xFF);
	_out(0x115, value & 0xFF);

	check(cylinder, sector);

	_out(HDA_CMDREG, FORMAT);

	_sleep(HDA_IRQ);
}

void format_n_sector(unsigned int cylinder, unsigned int sector, unsigned int size, unsigned int value) {
	int i;
	unsigned char* buffer = malloc(sizeof(unsigned char)*size);
	assert(buffer);

	for ( i = 0 ; i < size ; i++ ){
		buffer[i] = value;
	}

	write_n_sector(cylinder, sector, size, buffer);
	free(buffer);
}
