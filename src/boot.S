#include <kernel/abi.h>

.section .text
.code64
.global _start
_start:
	cli
	mov $(KERNEL_STACK_BOTTOM - 16), %rsp
	call startKernel

.global bootSystemCallRouter
bootSystemCallRouter:
	mov $(KERNEL_STACK_BOTTOM - 16), %rsp

	/* Mangled kernel::SystemCallRouter::route(int, U64, Address, U64, U64, U64) */
	call _ZN6kernel16SystemCallRouter5routeEimmmmm
