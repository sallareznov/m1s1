#include "../include/ctx_s.h"
#include <stdlib.h>
#include <assert.h>

struct ctx_s *current_ctx = NULL;

struct ctx_s *create_ctx(int stack_size, func_t f, void *args) {
	struct ctx_s *ctx;

	ctx = (struct ctx_s *) malloc(sizeof(struct ctx_s));
	ctx->state = ACTIVABLE;
	ctx->launcher = f;
	ctx->arg_launcher = args;
	ctx->stack = (char *) malloc(stack_size);
	assert(ctx->stack);
	ctx->v_esp = (char *) ctx->stack + stack_size;
	ctx->v_ebp = ctx->v_esp;
	ctx->magic = MAGIC;
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
		current_ctx->launcher(current_ctx->arg_launcher);
		current_ctx->state = TERMINATED;
		exit(EXIT_SUCCESS);
	}
	assert(current_ctx->state != TERMINATED);
}
