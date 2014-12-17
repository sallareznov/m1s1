#include "mmu.h"
#include "hardware.h"
#include "hwconfig.h"
#include "mi_user.h"
#include "mi_syscall.h"
#include <stdio.h>
#include <stdlib.h>

static int current_process;

static void mmuhandler() {
	unsigned int fault_addr, vpage, ppage;
	struct tlb_entry_s tlb;

	fault_addr = _in(MMU_FAULT_ADDR);
	vpage = vpage_of_vaddr(fault_addr);
	ppage = ppage_of_vaddr(current_process, fault_addr);

	if (ppage == -1) {
		fprintf(stderr, "My segmentation fault\n");
		exit(EXIT_FAILURE);
	}
	else {
		tlb.virt_page = vpage;
		tlb.phys_page = ppage;
		tlb.access_type = 0b111;
		tlb.is_active = 0b1;
		_out(TLB_ADD_ENTRY, *((unsigned int *) &tlb));
	}
}

static void empty_it(){
	return;
}

static void switch_to_process0(void) {
    current_process = 0;
    _out(MMU_CMD, MMU_RESET);
}

static void switch_to_process1(void) {
    current_process = 1;
    _out(MMU_CMD, MMU_RESET);
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
    IRQVECTOR[16] = switch_to_process0;
    IRQVECTOR[17] = switch_to_process1;
    _mask(0x1001);


    run();

    return EXIT_SUCCESS;
}
