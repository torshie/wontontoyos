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
	/* Save user stack pointer to the bottom of kernel stack */
	mov %rsp, %rax
	mov $(KERNEL_STACK_BOTTOM - 16), %rsp /* XXX Check whether set %rsp like this is safe */
	push %rax

	/* Save user instruction pointer */
	push %rcx

	/* Mangled kernel::SystemCallRouter::route(int, U64, U64, U64, U64, U64) */
	call _ZN6kernel16SystemCallRouter5routeEimmmmm

	/* Load user instruction pointer */
	pop %rcx

	/* Load user stack pointer */
	pop %rsp
	sysretq
