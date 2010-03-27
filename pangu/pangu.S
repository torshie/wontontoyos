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

globalDescriptorTablePointer:
	.short . - globalDescriptorTable - 1
	.long globalDescriptorTable
	.long 0

.align 8
pml4: .quad 0
loaderEntry: .quad 0

.section .text
.code32
bootstrap:
	cli

	mov $__ld_kernel_stack__, %esp /* Defined in ld script */

	call _createTemporaryPagingMap
	mov %eax, pml4 /* Save return value which is the address of level four map */

	/* Load the 64-bit loader into memory */
	pushl $0x1ff000 /* Modify loader.ld as well if this value is modified */
	pushl $(loaderEnd - loaderStart)
	pushl $loaderStart
	call _loadFileImage
	add $12, %esp

	mov %eax, loaderEntry

	/* Pass parameters to the 64-bit loader */
	movl $(dataSegmentDescriptor - globalDescriptorTable), -8(%eax)
	movl $kernelStart, -16(%eax)
	movl $(kernelEnd - kernelStart), -24(%eax)

	xor %eax, %eax
	bts $CR0_BIT_PROTECTION_ENABLED, %eax
	mov %eax, %cr0

	mov %cr4, %eax
	bts $CR4_BIT_PHYSICAL_ADDRESS_EXTENSION, %eax
	bts $CR4_BIT_PAGE_GLOBAL_ENABLE, %eax
	bts $CR4_BIT_OS_FXSAVE_FXRSTOR_SUPPORT, %eax
	mov %eax, %cr4

	mov pml4, %eax
	mov %eax, %cr3

	mov $MSR_EXTENDED_FEATURE_ENABLE_REGISTER, %ecx
	xor %edx, %edx
	xor %eax, %eax
	bts $EFER_BIT_NO_EXECUTE_ENABLE, %eax
	bts $EFER_BIT_LONG_MODE_ENABLE, %eax
	bts $EFER_BIT_SYSTEM_CALL_EXTENSION, %eax
	wrmsr

	lgdt globalDescriptorTablePointer

	mov %cr0, %eax
	bts $CR0_BIT_PAGING, %eax /* Enable paging */
	mov %eax, %cr0

	mov loaderEntry, %eax
	ljmp $(_64bitCodeSegmentDescriptor - globalDescriptorTable), $_64bit

.align 16
_64bit:
	cli
	.byte 0x48, 0x31, 0xc0 /* xor %rax, %rax */

	/*movq loaderEntry, %rax*/
	.byte 0x8b, 0x04, 0x25
	.long loaderEntry

	.byte 0xff, 0xe0 /* jmpq *%rax */

.section .data
.align 8
loaderStart:
	.incbin "../loader/loader.elf"
loaderEnd:

.align 8
kernelStart:
	.incbin "../src/kernel.elf"
kernelEnd:
