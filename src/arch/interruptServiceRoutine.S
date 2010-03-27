.altmacro

.macro LOAD_GENERIC_REGISTER
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %r11
	pop %r10
	pop %r9
	pop %r8
	pop %rbp
	pop %rdi
	pop %rsi
	pop %rdx
	pop %rcx
	pop %rbx
	pop %rax
.endm

.macro SAVE_GENERIC_REGISTER
	push %rax
	push %rbx
	push %rcx
	push %rdx
	push %rsi
	push %rdi
	push %rbp
	push %r8
	push %r9
	push %r10
	push %r11
	push %r12
	push %r13
	push %r14
	push %r15
.endm

.macro DEFINE_ISR isrNumber
	.align 8
	isr\isrNumber:
		cli /* XXX Use a gate descriptor to clear and set RFLAGS.IF */
		SAVE_GENERIC_REGISTER
		mov $\isrNumber, %rdi
		/* Mangled ::kernel::InterruptTable::handle(unsigned int) */
		call _ZN6kernel14InterruptTable6handleEj
		LOAD_GENERIC_REGISTER
		sti /* XXX Use a gate descriptor to clear and set RFLAGS.IF */
		iretq
.endm

.macro FOR from, to, action
	action \from
	.if \to - \from
		FOR %(\from + 1), \to, action
	.endif
.endm

.macro SET_ISR_ENTRY param
	.quad isr\param
.endm

.section .text
	FOR 0, 63, DEFINE_ISR
	FOR 64, 127, DEFINE_ISR

.section .data
.global isrTable
.align 8
isrTable:
	FOR 0, 63, SET_ISR_ENTRY
	FOR 64, 127, SET_ISR_ENTRY
