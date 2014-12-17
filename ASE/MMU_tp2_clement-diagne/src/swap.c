#include "../include/swap.h"
#include "../include/mmu.h"
#include "hardware.h"
#include <stdio.h>
#include <assert.h>

static FILE *swap_file;

void init_swap(const char *path){
    swap_file = fopen(path, "w+b");
    assert(swap_file);
}

/* Ecrire dans le fichier de swap
   vpage : ou ecrire les données dans le fichier
   ppage : ou lire les données dans la ram
 */
void store_to_swap(int vpage, int ppage) {
    int status;

    status = fseek(swap_file, vpage * PAGE_SIZE, SEEK_SET);
    assert(!status);
    fwrite(physical_memory + (ppage * PAGE_SIZE), PAGE_SIZE, 1, swap_file);
}


/* Recuperer la page du fichier de swap  
   vpage : ou lire les données dans le fichier
   ppage : ou ecrire dans la ram
 */
void fetch_from_swap(int vpage, int ppage) {
    int status;
    status = fseek(swap_file, vpage * PAGE_SIZE, SEEK_SET);
    assert(!status);
    fread(physical_memory + (ppage * PAGE_SIZE), PAGE_SIZE, 1, swap_file);
}