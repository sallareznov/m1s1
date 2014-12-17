#include "../include/pingpong.h"
#include "../include/ctx_s.h"
#include <stdio.h>
#include <stdlib.h>

void f_ping(void *args) {
	while (1) {
		printf("A");
		switch_to_ctx(ctx_pong);
		printf("B");
		switch_to_ctx(ctx_pong);
		printf("C");
		switch_to_ctx(ctx_pong);
	}
}

void f_pong(void *args) {
	while(1) {
		printf("1");
		switch_to_ctx(ctx_ping);
		printf("2");
		switch_to_ctx(ctx_ping);
	}
}

int main(int argc, char const *argv[]) {
	ctx_ping = create_ctx(16384, f_ping, NULL);
	ctx_pong = create_ctx(16384, f_pong, NULL);
	switch_to_ctx(ctx_ping);
	return EXIT_SUCCESS;
}