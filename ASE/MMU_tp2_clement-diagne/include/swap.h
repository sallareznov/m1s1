#ifndef _SWAP_H_
#define _SWAP_H_

void init_swap(const char *path);
void store_to_swap(int vpage, int ppage);
void fetch_from_swap(int vpage, int ppage);

#endif
