#ifndef _DIVIDE_H_
#define _DIVIDE_H_

#define MAXSIZE 1000000
#define MAGICNUMBER 7

void normalise(int x[], int y[], int y_x[]);
void calcule_nb_inversions_quadra(int tab[]);
void calcule_nb_inversions_log(int tab[]);
void calcule_distance_quadra(int x[], int y[]);
void calcule_distance_log(int x[], int y[]);
void affiche_tableau(int tab[]);

#endif
