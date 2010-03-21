#include <asm/LOAD_GENERIC_REGISTER.macro>
#include <asm/SAVE_GENERIC_REGISTER.macro>

.altmacro

.macro DEFINE_ISR isrNumber
	isr\isrNumber:
		cli
		SAVE_GENERIC_REGISTER
		mov $\isrNumber, %rdi
		/* Mangled ::kernel::InterruptDescriptorTable::handle */
		call _ZN6kernel24InterruptDescriptorTable6handleEi
		LOAD_GENERIC_REGISTER
		sti
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

.macro CREATE_ISR_TABLE size, tableName
	.section .text
		FOR 0, %(\size - 1), DEFINE_ISR
	.section .data
	.global \tableName
	.align 8
	\tableName:
		FOR 0, %(\size - 1), SET_ISR_ENTRY
.endm

/* XXX Check whether we need this many service routines */
CREATE_ISR_TABLE 32, isrAddressTable
