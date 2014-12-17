#include "ctx_s.h"
#include "pingpongpang.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hardware.h"
#include "hwconfig.h"

#define TRUE 1
#define FALSE 0

static int TMP = FALSE;

struct ctx_s *current_ctx = NULL;

struct ctx_s *create_ctx(int stack_size, func_t f, void *args) {
	struct ctx_s *ctx = (struct ctx_s *) malloc(sizeof(struct ctx_s));
	assert(ctx);
	ctx->state = ACTIVABLE;
	ctx->launcher_f = f;
	ctx->launcher_args = args;
	ctx->stack = (char *) malloc(stack_size);
	assert(ctx->stack);
	ctx->v_esp = ((char *) ctx->stack) + stack_size;
	ctx->v_ebp = ctx->v_esp;
	ctx->magic = MAGIC;
	if (current_ctx == NULL) {
		ctx->next = ctx;
		ctx->previous = ctx;
		current_ctx = ctx;
	}
	else {
		ctx->next = current_ctx;
		ctx->previous = current_ctx->previous;
		(current_ctx->previous)->next = ctx;		
		current_ctx->previous = ctx;
	}
	return ctx;
}

void switch_to_ctx(struct ctx_s *ctx) {
	if (current_ctx != NULL) {
		asm("movl %%esp, %0" : "=r"(current_ctx->v_esp));
		asm("movl %%ebp, %0" : "=r"(current_ctx->v_ebp));
	}
	assert(ctx->magic == MAGIC);
	current_ctx = ctx;
	asm("movl %0, %%esp" : : "r"(current_ctx->v_esp));
	asm("movl %0, %%ebp" : : "r"(current_ctx->v_ebp));
	if (current_ctx->state == ACTIVABLE) {
		current_ctx->state = READY;
		_mask(1);
		current_ctx->launcher_f(current_ctx->launcher_args);
		current_ctx->state = TERMINATED;

		delete_ctx();
		exit(EXIT_SUCCESS);
	}
}

void yield() {
	_out(TIMER_ALARM,0xFFFFFFFE);
	if (!TMP) {
		TMP = TRUE;
		switch_to_ctx(current_ctx);
	}
	else {
		switch_to_ctx(current_ctx->next);
	}
}

void delete_ctx() {
	char *tmp;
	struct ctx_s *last = current_ctx->previous;

	if (last == current_ctx) {
		exit(EXIT_SUCCESS);
	}
	last->next = current_ctx->next;
	(current_ctx->next)->previous = last;
	tmp = current_ctx->stack;
	free(current_ctx);
	current_ctx = last;
	free(tmp);
	yield();
}
