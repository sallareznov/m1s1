#ifndef _SEM_S_H_
#define _SEM_S_H_

struct sem_s {
  int cpt;
  struct ctx_s *first_blocked;
};

void sem_init(struct sem_s* sem, unsigned int val);
void sem_down(struct sem_s* sem);
void sem_up(struct sem_s* sem);

#endif
