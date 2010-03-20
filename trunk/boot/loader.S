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

/* Data Segment descriptor. */
dataSegmentDescriptor:
	.long 0x0000FFFF
	.long 0x00CF9200 /* Bit G, D/B, P, 12 and W are set, DPL is 0 */

/* 64-bit Code Segment descriptor */
_64bitCodeSegmentDescriptor:
	.long 0x00000000
	.long 0x00209800 /* Bit L, P, 12 and 11 are set, DPL is 0 */

globalDescriptorTablePointer:
	.short . - globalDescriptorTable - 1
	.quad globalDescriptorTable

.section .text
.code32
bootstrap:
	cli

	mov $__ld_kernel_stack__, %esp /* Defined in ld script */

	call _createTemporaryPagingMap
	push %eax /* Save return value which is the address of level four map */

	xor %eax, %eax
	bts $CR0_BIT_PROTECTION_ENABLED, %eax
	mov %eax, %cr0

	mov %cr4, %eax
	bts $CR4_BIT_PHYSICAL_ADDRESS_EXTENSION, %eax
	bts $CR4_BIT_PAGE_GLOBAL_ENABLE, %eax
	bts $CR4_BIT_OS_FXSAVE_FXRSTOR_SUPPORT, %eax
	mov %eax, %cr4

	popl %ebx /* We have saved address of pageMap after calling fillPageTable() */
	mov %ebx, %cr3

	mov $MSR_EXTENDED_FEATURE_ENABLE_REGISTER, %ecx
	xor %eax, %eax
	bts $EFER_BIT_NO_EXECUTE_ENABLE, %eax
	bts $EFER_BIT_LONG_MODE_ENABLE, %eax
	bts $EFER_BIT_SYSTEM_CALL_EXTENSION, %eax
	wrmsr

	lgdt globalDescriptorTablePointer

	mov %cr0, %eax
	bts $CR0_BIT_PAGING, %eax /* Enable paging */
	mov %eax, %cr0

	ljmp $(_64bitCodeSegmentDescriptor - globalDescriptorTable), $_64bitMode

.code64
_64bitMode:
	cli
	mov $__ld_kernel_stack__, %rsp
	push %rbx /* The address of pml4 */

	mov $(dataSegmentDescriptor - globalDescriptorTable), %ax
	mov %ax, %ds

	mov $kernelImage, %rdi
	mov $(kernelImageEnd - kernelImage), %rsi
	call loadKernelImage

	jmp *%rax /* Jump to kernel's entry point */

.section .data
.align 8
kernelImage:
.incbin "../src/kernel.elf"
kernelImageEnd:
