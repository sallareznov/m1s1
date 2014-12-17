#include "try.h"
#include <assert.h>

/* try(struct ctx_s, func_t, int): function that stores the execution context, executes the function f with the parameter arg, and returns the result */
int try(struct ctx_s *pctx, func_t *f, int arg) {
	asm("movl %%esp, %0" : "=r"(pctx->v_esp));
	asm("movl %%ebp, %0" : "=r"(pctx->v_ebp));
	return f(arg);
}

/* throw(struct ctx_s, int): function that restores the context saved by the try function and returns r */
int throw(struct ctx_s *pctx, int r) {
	static struct ctx_s *save_pctx;
	static int save_r;
	assert(pctx);
	save_pctx = pctx;
	save_r = r;
	asm("movl %0, %%esp" : : "r"(save_pctx->v_esp));
	asm("movl %0, %%ebp" : : "r"(save_pctx->v_ebp));
	return save_r;
}
