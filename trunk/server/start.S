#include <kernel/abi.h>

.section .init
.global start
start:
	mov $(USER_STACK_BOTTOM - 8), %rsp

	call main
	mov %rax, %rsi
	syscall
