#ifndef _MMU_H_
#define _MMU_H_

struct tlb_entry_s {
	unsigned unused: 8;
	unsigned virt_page: 12;
	unsigned phys_page: 8;
	unsigned access_type: 3;
	unsigned is_active: 1;
};

int vpage_of_vaddr(unsigned int vaddr);
int ppage_of_vaddr(unsigned int process, unsigned int vaddr);

#endif