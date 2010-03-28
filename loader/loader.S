#include <kernel/abi.h>

.section .text
.code64
.global _start
.align 16
	/* This area is used for passing parameters from 32-bit loader to 64-bit loader */
	.rept 8
		.quad 0
	.endr
_start:
	cli
	mov $__ld_kernel_stack__, %rsp

	mov _start - 8, %ax
	mov %ax, %ds
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	mov _start - 16, %rdi
	mov _start - 24, %rsi
	mov $KERNEL_PHYSICAL_BASE, %rdx
	xchg %bx, %bx
	call loadFileImage
	jmp *%rax /* Jump to kernel's entry point */
