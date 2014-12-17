#include "../include/mi_user.h"
#include "../include/mi_syscall.h"
#include "../include/mmu.h"
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_MATRIX 50		

extern void *virtual_memory;

typedef unsigned int matrix[N_MATRIX][N_MATRIX];


void init_matrix(matrix *m) {
	int i, j;

	for (j = 0 ; j < N_MATRIX ; j++) {
		for (i = 0 ; i < N_MATRIX ; i++) {
			(*m)[i][j] = (i + j) % 128;
		}
	}
}


void mult_matrix(matrix *a, matrix *b, matrix *result) {
	int i, j, k;

	for (i = 0 ; i < N_MATRIX ; i++) {
		for (j = 0 ; j < N_MATRIX ; j++) {
			for (k = 0 ; k < N_MATRIX ; k++) {
				(*result)[i][j] += (*a)[i][k] * (*b)[k][j];
			}
		}
	}
}

void printMatrice(matrix *a){
	int i, j;

	for (j = 0 ; j < N_MATRIX ; j++) {
		for (i = 0 ; i < N_MATRIX ; i++) {
			printf("%d\t",(*a)[i][j] );
		}
		printf("\n");
	}

}


void run() {
	matrix* m1= (matrix*)virtual_memory;
	matrix* m2= (matrix*)virtual_memory+1;
	matrix* m3= (matrix*)virtual_memory+2;

	init_matrix(m1);
	init_matrix(m2);

	mult_matrix(m1,m2,m3);

	printf("Matrice a :\n");
	printMatrice(m1);
	printf("Matrice b :\n");
	printMatrice(m2);
	printf("a * b :\n");
	printMatrice(m3);



	printf("DONE !\n");
}
