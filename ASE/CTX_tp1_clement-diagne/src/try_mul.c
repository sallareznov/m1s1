#include "../include/try.h"
#include <stdio.h>
#include <stdlib.h>

static struct ctx_s current_ctx;

/* mul(int): function that read numbers on the standard input and returns their product */
static int mul(int depth) {
	int i;

	switch (scanf("%d", &i)) {
		case EOF :
			return 1;
		case 0 :
			return mul(depth+1);
		case 1 :
			if (i)
				return i * mul(depth+1);
			else
				return throw(&current_ctx, 0);
	}
	return throw(&current_ctx, 0);
}

/* main function : prints the result of the mul function*/
int main() {
	int product;

	printf("A list of int please...\n");
	product = try(&current_ctx, mul, 0);
	printf("product = %d\n", product);
	return EXIT_SUCCESS;
}
