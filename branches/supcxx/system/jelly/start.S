#include <kernel/abi.h>

.section .init
.global _start
_start:
	mov $(USER_STACK_BOTTOM - 16), %rsp
	call main

	mov %rax, %rdi
	/* Mangled jelly::SystemCall<0>::call(int) */
	call _ZN5jelly10SystemCallILi0EE4callEi
