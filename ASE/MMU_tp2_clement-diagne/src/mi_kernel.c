#include "../include/mi_syscall.h"
#include "../include/mmu.h"
#include "../include/mi_user.h"
#include "../include/swap.h"
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int vpage_of_ppage = 0;


static void mmuhandler(){
  struct tlb_entry_s e;
  int vpage, ppage, fault_addr;

  fault_addr = _in(MMU_FAULT_ADDR);

  assert(fault_addr >= (unsigned int) virtual_memory );
  assert(fault_addr < (unsigned int) virtual_memory + VM_SIZE -1 );


  
  vpage = vpage_of_vaddr(fault_addr);
  ppage = ppage_of_vaddr(fault_addr);

  /* Swap mmh_handler */
  if ( ppage == -1 ){

  store_to_swap(vpage_of_ppage, 1); /* On a qu'une page en memoire physique pour cet ex */
  fetch_from_swap(vpage, 1); /* On a qu'une page de memoire physique pour cet ex */
  vpage_of_ppage = vpage;
  e.phys_page=1;
  _out(TLB_DEL_ENTRY,*((int*)&e));
  /* notre structure pour la mmu_cmd, cf notre handler de mi_kernel */
  e.virt_page = vpage;
  e.phys_page = 1;
  e.access_type = 7;
  e.is_active = 1;
  _out(TLB_ADD_ENTRY, *(unsigned int*)&e);  
  vpage_of_ppage = vpage;

  }else{ 

  /* Classic mmh_handler */

  e.virt_page = vpage;
  e.phys_page = ppage;
  e.access_type = 0b111;
  e.is_active = 0b1;
  _out(TLB_ADD_ENTRY, *((unsigned int *) &e));

  }

}


static void empty_it(){
  return;
}

int main(int argc, char **argv) {
    int i;
    
    if(init_hardware("hardware.ini") == 0) {
    	fprintf(stderr, "Error in hardware initialization\n");
    	exit(EXIT_FAILURE);
  	}	

  	/* Interrupt handlers */
  	for(i=0; i<16; i++) {
    	IRQVECTOR[i] = empty_it;
  	}

  	IRQVECTOR[MMU_IRQ] = mmuhandler;
    _mask(0x1001);

    init_swap("swap_file");

    run();

    return EXIT_SUCCESS;
}
