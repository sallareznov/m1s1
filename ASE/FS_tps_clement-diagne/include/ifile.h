#ifndef _IFILE_H_
#define _IFILE_H_

#include "drive.h"
#include "vol.h"

#define BLOCKSIZE HDA_SECTORSIZE
#define F_BLOCK_POS(pos) (pos / BLOCKSIZE)
#define TRUE 1
#define FALSE !TRUE
#define IFILE_EOF -1
#define IBLOCK_OF_POS(pos) (pos % BLOCKSIZE)

struct file_desc_t {
	unsigned int inumber;
	unsigned int size;
	unsigned int pos;
	unsigned char buf[BLOCKSIZE];
	unsigned int dirty;
  	unsigned int is_open;
};

unsigned int create_ifile(enum inode_type_e type, int current_vol);
void delete_ifile(unsigned int inumber, int current_vol);
void open_ifile(struct file_desc_t *fd, unsigned int inumber, int current_vol);
void flush_ifile(struct file_desc_t *fd, int current_vol);
unsigned int vblock_of_f_block(int inumber, int fblock, int needToAllocate, int current_vol);
void close_ifile(struct file_desc_t *fd, int current_vol);
void free_array(unsigned int* t, int size, int current_vol);
void seek2_ifile(struct file_desc_t *fd, int e_offset, int current_vol);
int read_ifile(struct file_desc_t *fd, void *buf, unsigned int nbyte);
int readc_ifile(struct file_desc_t *fd);
int write_c_ifile(struct file_desc_t *fd,  char c, int current_vol);
int write_ifile(struct file_desc_t *fd, const void *buf, unsigned int nbyte, int current_vol);

#endif
