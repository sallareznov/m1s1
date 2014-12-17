#ifndef _CTX_S_H_
#define _CTX_S_H_

#define MAGIC 0xCAFEBABE

typedef void (func_t) (void *);

enum state_e {
	ACTIVABLE,
	READY,
	TERMINATED
};

struct ctx_s {
	void *v_esp;
	void *v_ebp;
	enum state_e state;
	func_t *launcher;
	void *arg_launcher;
	char *stack;
	unsigned int magic;
};

struct ctx_s *create_ctx(int stack_size, func_t f, void *args);
void switch_to_ctx(struct ctx_s *ctx);

#endif
