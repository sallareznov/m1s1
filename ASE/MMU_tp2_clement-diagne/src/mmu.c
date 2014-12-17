#include "../include/mmu.h"
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>

extern void *virtual_memory;

int vpage_of_vaddr(unsigned int vaddr) {
  return ((vaddr >> 12) & 0xFFF);
}

int ppage_of_vaddr(unsigned int vaddr) {
	unsigned int vpage;

	/* Test si l'adresse est bien virtuelle */
	if(vaddr < (unsigned)virtual_memory || vaddr > ((unsigned)virtual_memory + VM_SIZE - 1)){
		return -1;
	}

	vpage = vpage_of_vaddr(vaddr);
	if(vpage < 0 || vpage > N)
	  return -1;
	return vpage+1;
}
