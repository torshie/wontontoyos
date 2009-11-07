#include <kernel/abi.h>

.section .init
.code64
.global _start
_start:
	cli
	mov $(KERNEL_VIRTUAL_BASE + KERNEL_LOAD_ADDRESS - 16), %rsp

	jmp .
