.macro INTERRUPT_SERVICE_ROUTINE isrNumber
	interruptServiceRoutine\isrNumber:
		PUSH_GENERAL_PURPOSE_REGISTERS
		mov $\isrNumber, %rdi

		/* Mangled InterruptDescriptorTable::handle */
		call _ZN6kernel24InterruptDescriptorTable6handleEi

		POP_GENERAL_PURPOSE_REGISTERS
		iretq
.endm

.macro PUSH_GENERAL_PURPOSE_REGISTERS
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

.macro POP_GENERAL_PURPOSE_REGISTERS
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

INTERRUPT_SERVICE_ROUTINE 0
INTERRUPT_SERVICE_ROUTINE 1
INTERRUPT_SERVICE_ROUTINE 2
INTERRUPT_SERVICE_ROUTINE 3
INTERRUPT_SERVICE_ROUTINE 4
INTERRUPT_SERVICE_ROUTINE 5
INTERRUPT_SERVICE_ROUTINE 6
INTERRUPT_SERVICE_ROUTINE 7
INTERRUPT_SERVICE_ROUTINE 8
INTERRUPT_SERVICE_ROUTINE 9
INTERRUPT_SERVICE_ROUTINE 10
INTERRUPT_SERVICE_ROUTINE 11
INTERRUPT_SERVICE_ROUTINE 12
INTERRUPT_SERVICE_ROUTINE 13
INTERRUPT_SERVICE_ROUTINE 14
INTERRUPT_SERVICE_ROUTINE 15
INTERRUPT_SERVICE_ROUTINE 16
INTERRUPT_SERVICE_ROUTINE 17
INTERRUPT_SERVICE_ROUTINE 18
INTERRUPT_SERVICE_ROUTINE 19
INTERRUPT_SERVICE_ROUTINE 20
INTERRUPT_SERVICE_ROUTINE 21
INTERRUPT_SERVICE_ROUTINE 22
INTERRUPT_SERVICE_ROUTINE 23
INTERRUPT_SERVICE_ROUTINE 24
INTERRUPT_SERVICE_ROUTINE 25
INTERRUPT_SERVICE_ROUTINE 26
INTERRUPT_SERVICE_ROUTINE 27
INTERRUPT_SERVICE_ROUTINE 28
INTERRUPT_SERVICE_ROUTINE 29
INTERRUPT_SERVICE_ROUTINE 30
INTERRUPT_SERVICE_ROUTINE 31

.global isrAddressTable
isrAddressTable:
	.quad interruptServiceRoutine0
	.quad interruptServiceRoutine1
	.quad interruptServiceRoutine2
	.quad interruptServiceRoutine3
	.quad interruptServiceRoutine4
	.quad interruptServiceRoutine5
	.quad interruptServiceRoutine6
	.quad interruptServiceRoutine7
	.quad interruptServiceRoutine8
	.quad interruptServiceRoutine9
	.quad interruptServiceRoutine10
	.quad interruptServiceRoutine11
	.quad interruptServiceRoutine12
	.quad interruptServiceRoutine13
	.quad interruptServiceRoutine14
	.quad interruptServiceRoutine15
	.quad interruptServiceRoutine16
	.quad interruptServiceRoutine17
	.quad interruptServiceRoutine18
	.quad interruptServiceRoutine19
	.quad interruptServiceRoutine20
	.quad interruptServiceRoutine21
	.quad interruptServiceRoutine22
	.quad interruptServiceRoutine23
	.quad interruptServiceRoutine24
	.quad interruptServiceRoutine25
	.quad interruptServiceRoutine26
	.quad interruptServiceRoutine27
	.quad interruptServiceRoutine28
	.quad interruptServiceRoutine29
	.quad interruptServiceRoutine30
	.quad interruptServiceRoutine31
