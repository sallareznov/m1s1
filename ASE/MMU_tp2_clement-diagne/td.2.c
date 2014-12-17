/*
 * TD 9 : MMU ( suite )
 *
 * 
 * 
 * 1) Organisation du fichier de swap : 1er octet du swap = 1er octet de la memoire physique
 */





static FILE *swap_file;

void init_swap(const char *path){
  swap_file = fopen(path, "rwb");
}

/* Ecrire dans le fichier de swap
   vpage : ou ecrire les données dans le fichier
   ppage : ou lire les données dans la ram
 */
void store_to_swap(int vpage, int ppage){
  fseek(swap_file, vpage*PAGE_SIZE, SEEK_SET);
  fwrite(physical_memory+ppage*PAGE_SIZE, PAGE_SIZE, 1, swap_file);
}


/* Recuperer la page du fichier de swap  
   vpage : ou lire les données dans le fichier
   ppage : ou ecrire dans la ram
 */
void fetch_from_swap(int vpage, int ppage){
  fseek(swap_file, vpage*PAGE_SIZE, SEEK_SET);
  fread(physical_memory+ppage*PAGE_SIZE, PAGE_SIZE, 1, swap_file);
}




int vpage_of_ppage = -1;
static void mmu_handler_1page(){
  tlb_entry e;
  assert(_in(MMU_FAULT_ADDR) >= virtual_memory && _in(MMU_FAULT_ADDR) < virtual_memory+VM_SIZE); 
  if ( vpage_of_ppage != -1 ){
    store_to_swap(vpage_of_ppage, 1); /* On a qu'une page en memoire physique pour cet ex */
  }
  vpage = (_in(MMU_FAULT_ADDR) - virtual_memory )/PAGE_SIZE;
  fetch_from_swap(vpage, 1); /* On a qu'une page de memoire physique pour cet ex */

  /* notre structure pour la mmu_cmd, cf notre handler de mi_kernel */
  e.vpage = vpage;
  e.ppage = 1;
  e.read = 1;
  e.write = 1;
  e.execute = 0;
  _out(MMU_CMD, MMU_RESET, *(int*)&e); /* car il n'y a qu'une seul adresse dans notre mmu */
  vpage_of_ppage = vpage;
}


/* A modifier
 *
int vpage_of_ppage[]; /* init a -1 */
static void mmu_handler_npage(){
  tlb_entry e;
  assert(_in(MMU_FAULT_ADDR) >= virtual_memory && _in(MMU_FAULT_ADDR) < virtual_memory+VM_SIZE); 
  if ( vpage_of_ppage != -1 ){
    store_to_swap(vpage_of_ppage, 1); /* On a qu'une page en memoire physique pour cet ex */
  }
  vpage = (_in(MMU_FAULT_ADDR) - virtual_memory )/PAGE_SIZE;
  fetch_from_swap(vpage, 1); /* On a qu'une page de memoire physique pour cet ex */

  /* notre structure pour la mmu_cmd, cf notre handler de mi_kernel */
  e.vpage = vpage;
  e.ppage = 1;
  e.read = 1;
  e.write = 1;
  e.execute = 0;
  _out(MMU_CMD, MMU_RESET, *(int*)&e); /* car il n'y a qu'une seul adresse dans notre mmu */
  vpage_of_ppage = vpage;
}


