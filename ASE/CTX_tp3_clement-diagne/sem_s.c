#include <stdlib.h>
#include "sem_s.h"
#include "ctx_s.h"
#include "hardware.h"
#include "hwconfig.h"
#include <assert.h>


void sem_init(struct sem_s* sem, unsigned int val){
  sem->cpt = val;
  sem->first_blocked = NULL;
}

void sem_down(struct sem_s* sem){
  _mask(15);
  sem->cpt--;
  if ( sem->cpt < 0 ){
    /* changer etat */
    current_ctx->state = BLOCKED;

    /* se rajouter dans la liste de la sem*/
    sem->first_blocked = current_ctx;



    _mask(1); 
    /* puis yield */
    yield();
    
  }else{
  _mask(1);
  }
}

void sem_up(struct sem_s* sem){
  struct ctx_s* tmp;

  _mask(15);
  sem->cpt++;
  if ( sem->cpt < 0 ){
  sem->first_blocked->state = ACTIVABLE;
  tmp = sem->first_blocked->next ;
  sem->first_blocked->next = NULL;
  sem->first_blocked = tmp;

  }
  _mask(1);
}
