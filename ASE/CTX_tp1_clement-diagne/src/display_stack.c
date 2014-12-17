#include <stdio.h>
#include <stdlib.h>

#define pgrs_in() printf("%s() --> entering\n", __func__)
#define pgrs_out() printf("%s() -- exiting\n", __func__)
#define pgrs_nb_in(nb) printf("%s(%d) --> entering\n", __func__, nb)
#define pgrs_nb_out(nb) printf("%s(%d) -- exiting\n", __func__, nb)

/* printer(int, int): prints the adresses of the parameters and the values of the registers EBP and ESP.
This function returns 0 */
int printer(int first_param, int last_param) {
	int first_var, last_var;
	void *v_esp, *v_ebp;

	first_var = 0;
	last_var = 1;

	pgrs_nb_in(first_param);

	/* récupération des valeurs d'ESP et d'EBP */
	asm("movl %%ebp, %0" : "=r"(v_ebp));
	asm("movl %%esp, %0" : "=r"(v_esp));

	/* affichage de la valeur d'EBP */
	printf("EBP_PRINTER : %08X\n", (unsigned int) v_ebp);

	/* affichage des adresses des variables locales */
	printf("first_var : %08X\n", (unsigned int) &first_var);
	printf("last_var : %08X\n", (unsigned int) &last_var);

	/* affichage de la valeur d'ESP */
	printf("ESP_PRINTER : %08X\n", (unsigned int) v_esp);

	if (first_param > 0) {
		printer(first_param - 1, last_param);
	}

	pgrs_nb_out(first_param);
	return 0;
}

int main() {
	int *v_esp, *v_ebp;
	const int first_param_nested = 10;
	const int first_param_successive = 0;
	const int last_param = 1;

	pgrs_in();

	/* récupération des valeurs d'ESP et d'EBP */
	asm("movl %%ebp, %0" : "=r"(v_ebp));
	asm("movl %%esp, %0" : "=r"(v_esp));

	/* affichage de la valeur d'EBP */
	printf("EBP_MAIN : %08X\n", (unsigned int) v_ebp);

	printf("\n");

	printf("### NESTED CALLS ###\n");
	/* affichage des adresses des paramètres */
	printf("first_param_nested = %08X\n", (unsigned int) &first_param_nested);
	printf("last_param = %08X\n", (unsigned int) &last_param);
	printer(first_param_nested, last_param);

	printf("\n");

	printf("### SUCCESSIVE CALLS ###\n");
	/* affichage des adresses des paramètres */
	printf("first_param_successive = %08X\n", (unsigned int) &first_param_successive);
	printf("last_param = %08X\n", (unsigned int) &last_param);
	printer(first_param_successive, last_param);
	printer(first_param_successive, last_param);
	printer(first_param_successive, last_param);

	printf("\n");
	
	/* affichage de la valeur d'ESP */
	printf("ESP_MAIN : %08X\n", (unsigned int) v_esp);

	pgrs_out();

	return EXIT_SUCCESS;
}
