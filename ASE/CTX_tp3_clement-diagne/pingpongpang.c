#include "pingpongpang.h"
#include "hardware.h"
#include "hwconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include "ctx_s.h"

#define OCC 100000000


static void empty_it(void) {
  return;
}

void f_ping(void *args) {
	int i;

	for (i = 0 ; i < OCC ; i++) {
		printf("ping\n");
	}
}

void f_pong(void *args) {
	int i;

	for (i = 0 ; i < OCC ; i++) {
		printf("pong\n");
	}
}

void f_pang(void *args) {
	int i;

	for (i = 0 ; i < OCC ; i++) {
		printf("pang\n");
	}
}

int main() {
	int i;
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

	ctx_ping = create_ctx(16384, f_ping, NULL);
	ctx_pong = create_ctx(16384, f_pong, NULL);
	ctx_pang = create_ctx(16384, f_pang, NULL);
	

	while(~0);

	exit(EXIT_SUCCESS);
}
