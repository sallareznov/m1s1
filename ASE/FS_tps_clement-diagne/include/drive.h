#ifndef _DRIVE_H_
#define _DRIVE_H_

#define SEEK 0x02
#define READ 0x04
#define WRITE 0x06
#define FORMAT 0x08
#define DSKNFO 0x16

#define HDA_CMDREG 0x3F6
#define HDA_IRQ 14
#define HDA_SECTORSIZE 256
#define HDA_MAXCYLINDER 16  
#define HDA_MAXSECTOR 16    

void seek_sector(unsigned int cylinder, unsigned int sector);

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
void write_sector(unsigned int cylinder, unsigned int sector, const unsigned char *buffer);
void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value);

void read_n_sector(unsigned int cylinder, unsigned int sector, unsigned int n, unsigned char *buffer);
void write_n_sector(unsigned int cylinder, unsigned int sector, unsigned int n, const unsigned char *buffer);
void format_n_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value);

#endif
