#ifndef _PING_PONG_H_
#define _PING_PONG_H_

#define NB_OCC 100

struct ctx_s *ctx_ping;
struct ctx_s *ctx_pong;

void f_ping(void *arg);
void f_pong(void *arg);

#endif