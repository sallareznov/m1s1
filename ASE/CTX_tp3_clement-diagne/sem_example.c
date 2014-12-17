#include <stdlib.h>
#include <stdio.h>
#include "ctx_s.h"
#include "sem_s.h"
#include "hardware.h"
#include "hwconfig.h"

#define N 100
#define OCC 10000

static int qt = 0;

struct ctx_s* producteur_ctx;
struct ctx_s* consommateur_ctx;

struct sem_s mutex, vide, plein;

typedef int objet_t;

void produire_objet(objet_t *objet){
  printf("produire un objet, buffer[%d]\n", qt);
}

void mettre_objet(objet_t object){
    qt++;
  printf("mettre un objet\n");
}

void retirer_objet(objet_t* object){
  qt--;
  printf("retirer un objet : %d\n", qt);
}

void utiliser_objet(objet_t object){
  printf("utiliser un objet\n");
}

void producteur (void* args) {
  objet_t objet ;
  int i;
  while (1) {
    for ( i = 0 ; i < OCC ; i++ ){} 
    produire_objet(&objet);           /* produire l'objet suivant */
    sem_down(&vide);                  /* dec. nb places libres */
    sem_down(&mutex);                 /* entree en section critique */
    mettre_objet(objet);              /* mettre l'objet dans le tampon */
    sem_up(&mutex);                   /* sortie de section critique */
    sem_up(&plein);                   /* inc. nb place occupees */
  }
}

void consommateur (void* args) {
  objet_t objet ;
  int i;
  while (1) {
    for ( i = 0 ; i < OCC ; i++ ){} 
    sem_down(&plein);                 /* dec. nb emplacements occupes */
    sem_down(&mutex);                 /* entree section critique */
    retirer_objet (&objet);           /* retire un objet du tampon */
    sem_up(&mutex);                   /* sortie de la section critique */
    sem_up(&vide);                    /* inc. nb emplacements libres */
    utiliser_objet(objet);            /* utiliser l'objet */
  }
}

static void empty_it(void) {
  return;
}

int main(){
  int i;

  sem_init(&mutex, 1);                /* controle d'acces au tampon */
  sem_init(&vide, N);                 /* nb de places libres */
  sem_init(&plein, 0);                /* nb de places occupees */


  if (init_hardware(HARDWARE_INI) == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }	

  for (i=0; i<16; i++)
    IRQVECTOR[i] = empty_it;

  IRQVECTOR[TIMER_IRQ] = yield;

  _out(TIMER_PARAM,128+64+32+8); /* reset + alarm on + 8 tick / alarm */
  _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick (at 0xFFFFFFFF) */

  _mask(1);

  producteur_ctx = create_ctx(16384, producteur, NULL);
  consommateur_ctx = create_ctx(16384, consommateur, NULL);

  while(~0);

  return EXIT_SUCCESS;
}
