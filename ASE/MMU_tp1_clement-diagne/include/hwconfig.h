#ifndef _HW_CONFIG_H_
#define _HW_CONFIG_H_

#define MMU_FAULT_ADDR 0xCD
#define MMU_IRQ 13
#define TLB_ADD_ENTRY 0xCE
#define TLB_ENTRIES 0x800
#define TLB_SIZE 32
#define MMU_CMD 0x66

#define PM_PAGES 256
#define VM_PAGES 4096

#define PAGE_SIZE 4096
#define PM_SIZE PM_PAGES * PAGE_SIZE
#define VM_SIZE VM_PAGES * PAGE_SIZE

#define N 255

#endif