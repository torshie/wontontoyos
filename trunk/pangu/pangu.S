#include <arch/X64Constant.h>

.set MBOOT_MAGIC, 0x1BADB002
.set MBOOT_FLAGS, (1 | (1 << 1) | (1 << 16))
.set MBOOT_CHECKSUM, (-(MBOOT_FLAGS + MBOOT_MAGIC))

.section .text
.code32
.global _start
_start:
	jmp bootstrap

.align 4
mbootheader:
	.long MBOOT_MAGIC
	.long MBOOT_FLAGS
	.long MBOOT_CHECKSUM
	.long mbootheader

	/* Defined in ld script */
	.long __ld_code_start__
	.long __ld_data_end__
	.long __ld_bss_end__

	.long _start

.section .data
globalDescriptorTable:
	.quad 0 /* Null segment descriptor, required by CPU specification */

/* 64-bit Code Segment descriptor */
_64bitCodeSegmentDescriptor:
	.long 0x00000000
	.long 0x00209800 /* Bit L, P, 12 and 11 are set, DPL is 0 */

/* Data Segment descriptor. */
dataSegmentDescriptor:
	.long 0x0000FFFF
	.long 0x00CF9200 /* Bit G, D/B, P, 12 and W are set, DPL is 0 */

.global _globalDescriptorTablePointer
_globalDescriptorTablePointer:
	.short . - globalDescriptorTable - 1
	.long globalDescriptorTable
	.long 0

.align 8
loaderEntry: .quad 0

.section .text
.code32
bootstrap:
	cli

	mov $__ld_kernel_stack__, %esp /* Defined in ld script */

	call _rise

	mov %eax, loaderEntry

	/* Pass parameters to the 64-bit loader */
	movl $(dataSegmentDescriptor - globalDescriptorTable), -8(%eax)
	movl $_kernelStart, -16(%eax)
	movl $(_kernelEnd - _kernelStart), -24(%eax)

	ljmp $(_64bitCodeSegmentDescriptor - globalDescriptorTable), $_64bit

.section .text
_64bit:
	cli
	.byte 0x48, 0x31, 0xc0 /* xor %rax, %rax */

	/*movq loaderEntry, %rax*/
	.byte 0x8b, 0x04, 0x25
	.long loaderEntry

	.byte 0xff, 0xe0 /* jmpq *%rax */

.section .data
.global _loaderStart, _loaderEnd, _kernelStart, _kernelEnd
.align 8
_loaderStart:
	.incbin "../loader/loader.elf"
_loaderEnd:

.align 8
_kernelStart:
	.incbin "../src/kernel.elf"
_kernelEnd:
