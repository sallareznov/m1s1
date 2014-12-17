#ifndef _MMU_H_
#define _MMU_H_

#define MMU_FAULT_ADDR 0xCD
#define MMU_IRQ 13
#define TLB_ADD_ENTRY 0xCE
#define TLB_ENTRIES 0x800
#define TLB_DEL_ENTRY 0xDE
#define TLB_SIZE 32
#define MMU_CMD 0x66

#define PAGE_SIZE 4096
#define PM_PAGES 256
#define VM_PAGES 4096


#define PM_SIZE (PM_PAGES * PAGE_SIZE)	/*calcul de la taille total des pages phys*/
#define VM_SIZE (VM_PAGES * PAGE_SIZE) 	/*calcul de la taille total des pages virtu*/

#define N 2

struct tlb_entry_s {
	unsigned unused: 8;
	unsigned virt_page: 12;
	unsigned phys_page: 8;
	unsigned access_type: 3;
	unsigned is_active: 1;
};

int vpage_of_vaddr(unsigned int vaddr);
int ppage_of_vaddr(unsigned int vaddr);

#endif
