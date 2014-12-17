#ifndef _TRY_H_
#define _TRY_H_

typedef int (func_t)(int);

struct ctx_s {
	void *v_ebp;
	void *v_esp;
};

int try(struct ctx_s *pctx, func_t *f, int arg);
int throw(struct ctx_s *pctx, int r);

#endif