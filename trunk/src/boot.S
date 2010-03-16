#include <kernel/abi.h>

.section .init
.code64
.global _start
_start:
	cli
	mov $(KERNEL_STACK_BOTTOM - 16), %rsp

	call startKernel
