#include "divide.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static int TAB_SIZE = 0;
static unsigned long NB_INVERSIONS = 0;

void normalise(int x[], int y[], int normalisee_yx[]) {
	int i;
	int *lref;

	lref = (int *) calloc(TAB_SIZE, sizeof(int));
	for (i = 0 ; i < TAB_SIZE ; i++) {
		lref[x[i]] = i;
	}

	for (i = 0 ; i < TAB_SIZE ; i++) {
		normalisee_yx[i] = lref[y[i]];
	}

	free(lref);
}

void calcule_nb_inversions_quadra(int tab[]) {
	int i;

	for (i = 0 ; i < TAB_SIZE - 1; i++) {
		int j;

		for (j = i + 1 ; j < TAB_SIZE ; j++) {
			if (tab[i] > tab[j]) {
				NB_INVERSIONS++;
			}
		}
	}
}

void fusionner(int tab[], int debut_gauche, int fin_gauche, int debut_droite, int fin_droite) {
	int *moitie_gauche, *moitie_droite;
	int taille_gauche, taille_droite, ind_tab, ind_gauche, ind_droite;

	moitie_gauche = (int *) calloc(fin_gauche - debut_gauche, sizeof(int));
	moitie_droite = (int *) calloc(fin_droite - debut_droite, sizeof(int));
	taille_gauche = fin_gauche - debut_gauche;
	taille_droite = fin_droite - debut_droite;
	ind_gauche = 0;
	ind_droite = 0;

	for (ind_tab = debut_gauche; ind_tab < fin_gauche; ind_tab++) {
		moitie_gauche[ind_gauche] = tab[ind_tab];
		ind_gauche++;
	}
	for (ind_tab = debut_droite; ind_tab < fin_droite; ind_tab++) {
		moitie_droite[ind_droite] = tab[ind_tab];
		ind_droite++;
	}

	ind_gauche = 0;
	ind_droite = 0;
	ind_tab = debut_gauche;
	while ((ind_gauche < taille_gauche) && (ind_droite < taille_droite)) {
		if (moitie_gauche[ind_gauche] < moitie_droite[ind_droite]) {
			tab[ind_tab] = moitie_gauche[ind_gauche];
			ind_gauche++;
		}
		else {
			tab[ind_tab] = moitie_droite[ind_droite];
			NB_INVERSIONS += taille_gauche - ind_gauche;
			ind_droite++;
		}
		ind_tab++;
	}

	while (ind_gauche < taille_gauche) {
		tab[ind_tab] = moitie_gauche[ind_gauche];
		ind_tab++;
		ind_gauche++;
	}
	while (ind_droite < taille_droite) {
		tab[ind_tab] = moitie_droite[ind_droite];
		ind_tab++;
		ind_droite++;
	}

	free(moitie_gauche);
	free(moitie_droite);
}

void tri_fusion(int tab[], int debut, int fin) {
	if (fin - debut <= 1) {
		return;
	}
 	else {
 		int debut_gauche, fin_gauche, debut_droite, fin_droite;
 		debut_gauche = debut;
 		fin_gauche = (fin + debut) / 2;
 		debut_droite = fin_gauche;
 		fin_droite = fin;
 		tri_fusion(tab, debut_gauche, fin_gauche);
		tri_fusion(tab, debut_droite, fin_droite);
 		fusionner(tab, debut_gauche, fin_gauche, debut_droite, fin_droite);
 	}
}

void calcule_nb_inversions_log(int tab[]) {
	tri_fusion(tab, 0, TAB_SIZE);
}

void calcule_distance_quadra(int x[], int y[]) {
	int *normalisee_yx;

	normalisee_yx = (int *) calloc(TAB_SIZE, sizeof(int));

	/* normalisation de y par rapport à x */
	normalise(x, y, normalisee_yx);
	/* calcul de la distance entre x et y */
	calcule_nb_inversions_quadra(normalisee_yx);
	free(normalisee_yx);
}

void calcule_distance_log(int x[], int y[]) {
	int *normalisee_yx;

	normalisee_yx = (int *) calloc(TAB_SIZE, sizeof(int));

	/* normalisation de y par rapport à x */
	normalise(x, y, normalisee_yx);
	/* calcul de la distance entre x et y */
	calcule_nb_inversions_log(normalisee_yx);
	free(normalisee_yx);
}

void affiche_tableau(int tab[]) {
	int i;

	printf("[| %d ", tab[0]);
	for (i = 1 ; i < TAB_SIZE ; i++) {
		printf("; %d ", tab[i]);
	}
	printf("|]\n");
}

void usage() {
	fprintf(stderr, "./divide n < ex.dat\n");
	fprintf(stderr, "n = 0 => distance_quadra\n");
	fprintf(stderr, "n = 1 => distance_log\n");
	fprintf(stderr, "ex.dat = ex1.dat || ex2.dat || ex3.dat || ex4.dat || ex5.dat || ex6.dat || ex7.dat\n");
}

int main(int argc, char *argv[]) {
	int cible;
	int x[MAXSIZE], y[MAXSIZE];
	int i;
	int n;

	if (argc < 2) {
		usage();
		return 1;
	}

	n = atoi(argv[1]);

	/* récupération de la taille des tableaux */
	scanf("%d", &cible);
	TAB_SIZE = cible;

	/* récupération des valeurs de x */
	for (i = 0 ; i < TAB_SIZE ; i++) {
		scanf("%d", &cible);
		x[i] = cible;
	}

	/* récupération des valeurs de y */
	for (i = 0 ; i < TAB_SIZE ; i++) {
		scanf("%d", &cible);
		y[i] = cible;
	}

	switch (n) {
		case 0 : {
			calcule_distance_quadra(x, y);
			printf("distance_quadra = %ld\n", NB_INVERSIONS);
			return 0;
		}
		case 1 : {
			calcule_distance_log(x, y);
			printf("distance_log = %ld\n", NB_INVERSIONS);
			return 0;
		}
		default : {
			usage();
			return 1;
		}
	}

}
