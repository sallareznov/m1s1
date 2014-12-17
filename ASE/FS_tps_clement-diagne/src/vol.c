#include "../include/vol.h"
#include "../include/drive.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct mbr_s mbr;
extern struct super_block_s super_block;
extern int current_vol;

void load_mbr(){
  read_n_sector(0, 0, sizeof(struct mbr_s), (unsigned char*) &mbr);
  if (mbr.magic != MAGIC_VALUE){
    mbr.magic = MAGIC_VALUE;
    mbr.n_vol = 0;
  }
}

void save_mbr(){
  if ( mbr.magic == MAGIC_VALUE){
    write_n_sector(0, 0 , sizeof(struct mbr_s), (unsigned char*) &mbr);
  }
}

int sector_of_block(int vol, int block){
  assert(mbr.magic == MAGIC_VALUE);
  assert(vol< MAX_VOL);
  return ( mbr.vol[vol].first_sector + block ) % HDA_MAXSECTOR;
}


int cylinder_of_block(int vol, int block){
  assert(mbr.magic == MAGIC_VALUE);
  assert(vol< MAX_VOL);
  return (( mbr.vol[vol].first_sector + block ) / HDA_MAXSECTOR) + mbr.vol[vol].first_cylinder;
}

void read_block(int vol, int block, unsigned char* buff){
  read_sector(cylinder_of_block(vol, block),
	      sector_of_block(vol, block),
	      buff);
  return;
}


void write_block(int vol, int block, unsigned char* buff){
  write_sector(cylinder_of_block(vol, block),
	      sector_of_block(vol, block),
	      buff);
  return;
}


void read_n_block(int vol, int block, int size, unsigned char* buff){
  read_n_sector(cylinder_of_block(vol, block),
        sector_of_block(vol, block),
        size,
        buff);
  return;
}


void write_n_block(int vol, int block, int size, unsigned char* buff){
  write_n_sector(cylinder_of_block(vol, block),
        sector_of_block(vol, block),
        size,
        buff);
  return;
}


void format_block(int vol, int block, int value){
  format_sector(cylinder_of_block(vol, block),
        sector_of_block(vol, block),
        value);
  return;
}
void format_n_block(int vol, int block, int size, int value){
  format_n_sector(cylinder_of_block(vol, block),
        sector_of_block(vol, block),
        size,
        value);
  return;
}

char *enum_to_text(enum vol_type_e vol_type) {
  switch(vol_type) {
    case BASE : return "BASE";
    case ANNEXE : return "ANNEXE";
    default : return "OTHER";
  }
}

int check_before_create(int first_cylinder, int first_sector, int n_block){
  int i;
  int end_cylinder;
  int end_sector;
  for ( i = 0 ; i < mbr.n_vol ; i++ ){
    end_cylinder = (mbr.vol[i].first_cylinder + mbr.vol[i].n_block) / HDA_MAXSECTOR;
    end_sector = (mbr.vol[i].first_cylinder + mbr.vol[i].n_block) % HDA_MAXSECTOR;
    
    if ( (mbr.vol[i].first_cylinder <= first_cylinder && first_cylinder <= end_cylinder) ||
        (mbr.vol[i].first_sector <= first_sector && first_sector <= end_sector)){

      printf("Cannot create volume at this position because overlapse volume %d\n.", i);
      exit(EXIT_FAILURE);
    }
  }


  return 1;


}

void print_vol(struct vol_desc_s vol) {
  printf("\tfirst cylinder : \t%d\n", vol.first_cylinder);
  printf("\tfirst sector : \t\t%d\n", vol.first_sector);
  printf("\tnumber of blocks : \t%d\n", vol.n_block);
  printf("\ttype of volume : \t%s\n", enum_to_text(vol.type));
  printf("\tSUPER_BLOCK : \n");
  printf("\t\t- name : \t%s\n", super_block.name);
  printf("\t\t- serial : \t%d\n", super_block.serie);
  printf("\t\t- first_free : \t%d\n", super_block.first_free);
  printf("\t\t- available : \t%d\n", super_block.free_size);
} 



void init_super(int vol, char* name, uint32_t s, int blocks){
  int i;
  struct free_block_s fb;

  super_block.magic = MAGIC_VALUE;
  printf("Setting MagicValue\n");
  super_block.root_block = 0;
  super_block.serie = s;
  super_block.first_free = 1;
  super_block.free_size = blocks-1;
  strncpy(super_block.name, name, SUPER_BLOCK_NAME_SIZE);
  for ( i = 1 ; i < mbr.vol[vol].n_block-1 ; i ++ ){
    fb.next = i+1; 
    write_block(vol, i, (unsigned char*) &fb);
  }

  fb.next = 0;
  write_block(vol, mbr.vol[vol].n_block-1, (unsigned char*) &fb);


}
void load_super(int vol){
  read_n_block(vol, 0 , sizeof(struct super_block_s), (unsigned char*) &super_block);
  assert(super_block.magic == MAGIC_VALUE);

}
void save_super(int vol){
  assert(super_block.magic == MAGIC_VALUE);
  write_n_block(vol, 0, sizeof(struct super_block_s), (unsigned char*) &super_block);
}


unsigned int new_block(int vol){
  int retValue = super_block.first_free;
  struct free_block_s fb;

  if ( super_block.free_size == 0 ){
    return BLOCK_NULL;
  }

  read_n_block(vol, retValue, sizeof(struct free_block_s), (unsigned char*)&fb);
  super_block.first_free = fb.next;

  super_block.free_size--;
  save_super(vol);
  return retValue; 
}


/*    ^
*    / \
*   / | \
*  /  |  \
* /___°___\
*
*
* Attention, il n'y a pas de verification, on peut free deux fois le même block, augmentant la taille libre et modifiant notre liste chaîné.
*/
void free_block(int vol, unsigned int block){
  struct free_block_s fb;
  fb.next = super_block.first_free;

  write_n_block(vol, block, sizeof(struct free_block_s), (unsigned char*)&fb);

  super_block.first_free = block;
  
  super_block.free_size++;

  save_super(vol);



}
