#ifndef _CTX_S_H_
#define _CTX_S_H_

#define MAGIC 0xCAFEBABE

extern struct ctx_s* current_ctx;

typedef void (func_t) (void *);

enum state_e { ACTIVABLE, READY, TERMINATED, BLOCKED };

struct ctx_s {
  void *v_esp;
  void *v_ebp;
  enum state_e state;
  func_t *launcher_f;
  void *launcher_args;
  char *stack;
  unsigned int magic;
  struct ctx_s *next;
  struct ctx_s *previous;
  struct ctx_s *next_blocked;
  struct ctx_s *previous_blocked;
};

struct ctx_s *create_ctx(int stack_size, func_t f, void *args);
void switch_to_ctx(struct ctx_s *ctx);
void yield();
void delete_ctx();


#endif
