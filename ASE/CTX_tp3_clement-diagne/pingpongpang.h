#ifndef _PINGPONG_H_
#define _PINGPONG_H_

struct ctx_s *ctx_ping;
struct ctx_s *ctx_pong;
struct ctx_s *ctx_pang;

void f_ping(void *args);
void f_pong(void *args);
void f_pang(void *args);

#endif
