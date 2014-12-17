#include "../include/ifile.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int create_ifile(enum inode_type_e type, int current_vol){
  struct inode_s inode;
  int i;
  unsigned int inumber; 

  inode.type = type;
  inode.size = 0;
  for ( i = 0 ; i < DIRECT_SIZE ; i++ ){
    inode.direct[i] = BLOCK_NULL;
  }
  inode.indirect = BLOCK_NULL;
  inode.indirect2 = BLOCK_NULL;

  inumber = new_block(current_vol);
  if ( !inumber ){
    return BLOCK_NULL;
  }
  write_block(current_vol, inumber, (unsigned char *) &inode);
  return inumber;
}

void delete_ifile(unsigned int inumber, int current_vol){
  struct inode_s inode;
  unsigned int t[NB_INDIRECT];
  unsigned int t2[NB_INDIRECT];
  int i;

  read_n_block(current_vol, inumber, sizeof(struct inode_s), (unsigned char *)&inode);
  free_array(inode.direct, DIRECT_SIZE, current_vol);
  if ( inode.indirect != BLOCK_NULL){
    read_block(current_vol, inode.indirect, (unsigned char *) t);
    free_array(t, NB_INDIRECT, current_vol);
    free_block(current_vol, inode.indirect);
  }
  if ( inode.indirect2 != BLOCK_NULL ){
    read_block(current_vol, inode.indirect2, (unsigned char *) t2);
    for ( i = NB_INDIRECT - 1 ; i >= 0; i-- ){
      if ( t2[i] != BLOCK_NULL ){
	read_block(current_vol, t2[i], (unsigned char *) t);
	free_array(t, NB_INDIRECT, current_vol);
	free_block(current_vol, t2[i]);
      }
    }
    free_block(current_vol, inode.indirect2);
  }
  free_block(current_vol, inumber);

  /*
   * Faire les boucles dans le sens inverses, pour eviter les problèmes de l'insertion en tête
   */
}

void open_ifile(struct file_desc_t *fd, unsigned int inumber, int current_vol){
  struct inode_s inode;
  read_block(current_vol, inumber, (unsigned char *) &inode);
  fd->inumber = inumber;
  fd->size = inode.size;
  fd->pos = 0;
  if ( inode.direct[0] == BLOCK_NULL ){
    inode.direct[0] = new_block(current_vol);
    write_block(current_vol, inumber, (unsigned char *) &inode);
  }
  read_block(current_vol, inode.direct[0], fd->buf);
  fd->dirty = FALSE; 
  fd->is_open = TRUE;
}

void flush_ifile(struct file_desc_t *fd, int current_vol){
  unsigned int fblock;
  unsigned int vblock;
  assert(fd->is_open == TRUE);
  if ( fd->dirty ){
    fblock = F_BLOCK_POS(fd->pos);
    vblock = vblock_of_f_block(fd->inumber, fblock, TRUE, current_vol);
    assert(vblock != 0);
    write_block(current_vol, vblock, fd->buf);
    fd->dirty = FALSE;
  }
}

unsigned int vblock_of_f_block(int inumber, int fbloc, int needToAllocate, int current_vol){
  struct inode_s inode;
  int indirect[NB_INDIRECT];
  int indirect2[NB_INDIRECT];
  int d_indirect;

  read_block(current_vol, inumber, (unsigned char *) &inode);

  if (fbloc < DIRECT_SIZE){
    if (inode.direct[fbloc] == 0)
      {
	if (needToAllocate == TRUE)
	  {
	    inode.direct[fbloc] = new_block(current_vol);
	    write_block(current_vol, inumber, (unsigned char *) &inode);
	  }
	else return 0;
      }
    return inode.direct[fbloc];
  }

  fbloc -= DIRECT_SIZE;

  if (fbloc < NB_INDIRECT){
    if (inode.indirect == 0)
      {
	if (needToAllocate == TRUE)
	  {
	    inode.indirect = new_block(current_vol);
	    write_block(current_vol, inumber, (unsigned char *) &inode);
	  }
	else return 0;
      }

    read_block (current_vol, inode.indirect, (unsigned char*) indirect);

    if (indirect[fbloc] == 0)
      {
	if (needToAllocate == TRUE)
	  {
	    indirect[fbloc] = new_block(current_vol);
	    write_block (current_vol, inode.indirect, (unsigned char*) indirect);
	  }
	else return 0;
      }

    return indirect[fbloc];
  }

  fbloc -= NB_INDIRECT;
	
  if (fbloc > NB_INDIRECT*NB_INDIRECT)
    return 0;
	
  if (inode.indirect2 == 0)	{
    if (needToAllocate == TRUE)
      {
	inode.indirect2 = new_block(current_vol);
	write_block(current_vol, inumber, (unsigned char *) &inode);
      }
    else return 0;
  }
	
  read_block(current_vol, inode.indirect2, (unsigned char*) indirect2);
  d_indirect = fbloc / (NB_INDIRECT);
	
  if (indirect2[d_indirect] == 0)
    {
      if (needToAllocate == TRUE)
	{
	  indirect2[d_indirect] = new_block(current_vol);
	  write_block (current_vol, inode.indirect2, (unsigned char*) indirect2);
	}
      else return 0;
    }

  read_block (current_vol, indirect2[d_indirect], (unsigned char*) indirect);
  d_indirect = fbloc % (NB_INDIRECT);

  if (indirect[d_indirect] == 0)
    {
      if (needToAllocate == TRUE)
	{
	  indirect[d_indirect] = new_block(current_vol);
	  write_block (current_vol, indirect2[fbloc / (NB_INDIRECT)], (unsigned char*) indirect);
	}
      else return 0;
    }

  return indirect[d_indirect];
}


void close_ifile(struct file_desc_t *fd, int current_vol){
  struct inode_s inode;

  assert(fd->is_open == TRUE);
  flush_ifile(fd, current_vol);

  read_n_block(current_vol, fd->inumber, sizeof(struct inode_s), (unsigned char *)&inode);
  inode.size = fd->size;
  write_block(current_vol, fd->inumber, (unsigned char *) &inode);

  fd->is_open = FALSE;
}

void free_array(unsigned int* t, int size, int current_vol){
  int i;
  for ( i = size - 1 ; i >= 0 ; i--){
    if ( t[i] ){
      free_block(current_vol, t[i]);
    }
  }
}

void seek2_ifile(struct file_desc_t *fd, int e_offset, int current_vol){
    unsigned int old_pos = fd->pos;
    unsigned int fbloc, vbloc; 
  
    assert(fd->is_open == TRUE);
    assert(fd->pos + e_offset >= 0);
  
  
    /* update the position */
    fd->pos += e_offset;

    /* does the seek imply a jump in another bloc? */
    if (F_BLOCK_POS(fd->pos) != F_BLOCK_POS(old_pos)) {
	/* flush */
      flush_ifile(fd, current_vol);
    
	/* the bloc index of the new buffer */
	fbloc = F_BLOCK_POS(fd->pos);
	vbloc = vblock_of_f_block(fd->inumber, fbloc, FALSE, current_vol);

	if (! vbloc)
	    /* the bloc #0 is full of zeros */
	    memset(fd->buf, 0, BLOCKSIZE);
	else
	    /* load the bloc */
	    read_block(current_vol, vbloc, fd->buf);
    }

}

int read_ifile(struct file_desc_t *fd, void *buf, unsigned int nbyte){
  unsigned int i;
  int c; 
  
  /* eof? */
  if (fd->pos > fd->size)
    return IFILE_EOF; 
  
  /* read one by one */
  for (i = 0; i < nbyte; i++) {
    if ((c = readc_ifile(fd)) == IFILE_EOF) {
      return i; 
    }
    *((char *)buf+i) = c; 
  }
  
  return i;
}


int 
readc_ifile(struct file_desc_t *fd)
{
    char c;
    
    /* eof? */
    if (fd->pos > fd->size)
	return IFILE_EOF; 

    /* the data is in the buffer, just return it */
    c = fd->buf[IBLOCK_OF_POS(fd->pos)];
    
    /* seek + 1 */
    seek2_ifile(fd, 1, 0);
    
    return c; 
}

int write_ifile(struct file_desc_t *fd, const void *buf, unsigned int nbyte, int current_vol) {
    unsigned int i; 

    /* write one by one */
    for (i = 0; i < nbyte; i++) {
      if (write_c_ifile(fd, *((char *)buf+i), current_vol) == EXIT_FAILURE)
	  return EXIT_FAILURE;
    }

    return nbyte;
}

int write_c_ifile(struct file_desc_t *fd, char c, int current_vol){
  unsigned int ibloc;

    fd->buf[IBLOCK_OF_POS(fd->pos)] = c;
    if (! fd->dirty) {
      ibloc = vblock_of_f_block(fd->inumber, F_BLOCK_POS(fd->pos), TRUE, current_vol);
        if (! ibloc) 
	  return EXIT_FAILURE;
        fd->dirty = TRUE;
    }
    
    if (IBLOCK_OF_POS(fd->pos) == BLOCKSIZE-1) {
      ibloc = vblock_of_f_block(fd->inumber, F_BLOCK_POS(fd->pos), FALSE, current_vol);
	write_block(current_vol, ibloc, fd->buf);
	ibloc = vblock_of_f_block(fd->inumber,
				  F_BLOCK_POS(fd->pos+1), FALSE, current_vol);
	if (! ibloc) 
	    memset(fd->buf, 0, BLOCKSIZE);
	else
	    read_block(current_vol, ibloc, fd->buf);
	fd->dirty = FALSE;
    }
    
    if (fd->size < fd->pos)
	fd->size = fd->pos;
    fd->pos++;
    
    return fd->pos - 1;
}
