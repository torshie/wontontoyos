#include <kernel/abi.h>

.section .text
.code64
.global _start
_start:
	cli
	mov $(KERNEL_STACK_BOTTOM - 16), %rsp
	call startKernel

.global bootServiceRouter
bootServiceRouter:
	/* Save user stack pointer to the bottom of kernel stack */
	mov %rsp, %rax
	mov $(KERNEL_STACK_BOTTOM - 16), %rsp /* XXX Check whether set %rsp like this is safe */
	push %rax

	push %r11 /* Save user RFLAGS */
	push %rcx /* Save user instruction pointer */

	sti

	/* Mangled kernel::ServiceRouter::route(int, U64, U64, U64, U64, U64) */
	call _ZN6kernel13ServiceRouter5routeEimmmmm

	pop %rcx /* Load user instruction pointer */
	pop %r11 /* Load user RFLAGS */
	pop %rsp /* Load user stack pointer */
	sysretq
