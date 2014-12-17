#include "mmu.h"
#include "hardware.h"
#include "hwconfig.h"

extern void *virtual_memory;

int vpage_of_vaddr(unsigned int vaddr) {
	return ((vaddr >> 12) & 0xFFF);
}

int ppage_of_vaddr(unsigned int process, unsigned int vaddr) {
	unsigned int vpage;

	if ((vaddr < (unsigned) virtual_memory) || (vaddr > (unsigned) virtual_memory + VM_SIZE - 1)) {
		return -1;
	}

	vpage = vpage_of_vaddr(vaddr);
	if ((vpage < 0) || (vpage > N/2))
		return -1;
	else
		return (process * (N/2)) + vpage + 1;
}
