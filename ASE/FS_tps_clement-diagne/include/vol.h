#include <stdint.h>
#include "drive.h"

#define MAX_VOL 8
#define MAGIC_VALUE 0xB16B00B5
#define DIRECT_SIZE ((HDA_SECTORSIZE-20)/4)
#define NB_INDIRECT (HDA_SECTORSIZE / 4)
#define SUPER_BLOCK_NAME_SIZE 32
#define BLOCK_NULL 0

enum vol_type_e{
  BASE, ANNEXE, OTHER
};

enum inode_type_e{
	REPOSITORY, REG_FILE
};

struct vol_desc_s {
  int first_cylinder;
  int first_sector;
  int n_block;
  enum vol_type_e type;
};

struct mbr_s {
  int magic;
  int n_vol;
  struct vol_desc_s  vol[MAX_VOL];
};

struct super_block_s {
	int magic;
	int serie;
	char name[SUPER_BLOCK_NAME_SIZE];
	int root_block;
	int first_free;
	int free_size;
};

struct free_block_s{
	int next;
};

struct inode_s{
	enum inode_type_e type;
	unsigned int size;
	unsigned int direct[DIRECT_SIZE];
	unsigned int indirect;
	unsigned int indirect2;
};


struct mbr_s mbr;
struct super_block_s super_block;
int current_vol;


/* to implement */
void load_mbr();
void save_mbr();
int sector_of_block(int vol, int block);
int cylinder_of_block(int vol, int block);
void read_block(int vol, int block, unsigned char* buff);
void read_n_block(int vol, int block, int size, unsigned char* buff);
void write_block(int vol, int block, unsigned char* buff);
void write_n_block(int vol, int block, int size, unsigned char* buff);
void format_block(int vol, int block, int value);
void format_n_block(int vol, int block, int size, int value);

void format_vol(int vol);


void print_vol(struct vol_desc_s vol);
int check_before_create(int first_cylinder, int first_sector, int n_block);


void init_super(int vol, char* name, uint32_t s, int blocks);
void load_super(int vol);
void save_super(int vol);

unsigned int new_block(int vol);
void free_block(int vol, unsigned int block);