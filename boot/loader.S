/**
 * 64-bit kernel loader.
 * It does the following:
 * 1. Create 64-bit identity map, maps the lower 2M memory, meanwhile it
 *    maps the this area into higher half, started at 0xFFFFFF0000000000
 *    (the last but one entry in the level four paging structure)
 * 2. The kernel executable will be wrapped into boot loader with .incbin
 *    gas directive.
 * 3. Use SimpleLoader to parse and load the kernel executable
 * 4. Pass kernel's memory layout to kernel (TODO This hasn't been fully
 *    implemented)
 * 5. Jump to the kernel's entry point
 */
.set MBOOT_MAGIC, 0x1BADB002
.set MBOOT_FLAGS, (1 | (1 << 1) | (1 << 16))
.set MBOOT_CHECKSUM, (-(MBOOT_FLAGS + MBOOT_MAGIC))
.set PAGE_SIZE, 0x1000

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

/**
 * Data Segment descriptor.
 */
dataSegmentDescriptor:
	.long 0x0000FFFF
	.long 0x00CF9200 /* Bit G, D/B, P, 12 and W are set, DPL is 0 */

/**
 * 64-bit Code Segment descriptor
 */
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

	call fillPageTable
	pushl %eax /* Save return value which is the address of level four
				* map
				*/

	mov $0x1, %eax
	mov %eax, %cr0

	mov %cr4, %eax
	bts $5, %eax /* Set PAE */
	bts $7, %eax /* Set PGE */
	mov %eax, %cr4

	/* Point cr3 at pageMap. See fillPageTable() for why it is 0x10a000 */
	popl %ebx /* We have saved address of pageMap after calling
			   * fillPageTable()
			   */
	mov %ebx, %cr3

	mov $0x00C0000080, %ecx /* EFER MSR */
	rdmsr
	xor %eax, %eax
	bts $11, %eax /* No execute */
	bts $8, %eax /* Long Mode Enable */
	bts $0, %eax /* System Call Extensions */
	wrmsr

	lgdt globalDescriptorTablePointer

	mov %cr0, %eax
	bts $31, %eax /* Enable paging */
	mov %eax, %cr0

	ljmp $(_64bitCodeSegmentDescriptor - globalDescriptorTable), $_64bitMode

.code64
_64bitMode:
	cli
	mov $__ld_kernel_stack__, %rsp
	push %rbx /* The address of pml4 */

	mov $(dataSegmentDescriptor - globalDescriptorTable), %ax
	mov %ax, %ds

	/**
	 * loadKernelImage() is compiled to 64-bit code, so use 64-bit
	 * calling convention
	 */
	mov $kernelImage, %rdi
	mov $(kernelImageEnd - kernelImage), %rsi
	call loadKernelImage

	jmp *%rax /* Jump to kernel's entry point */

	mov $0xB8000, %edi
	mov $0x0f620f2d0f340f36, %rax
	mov %rax, (%edi)

	mov $0x0f6d0f200f640f69, %rax
	mov %rax, 8(%edi)

	mov $0x0f200f650f640f6f, %rax
	mov %rax, 16(%edi)

	jmp .

.section .data
kernelImage:
.incbin "../src/kernel.elf"
kernelImageEnd:
	jmp .
