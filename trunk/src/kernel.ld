OUTPUT_ARCH(i386:x86-64)
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

/**
 * If you want to change load address, make sure abi.h is consistent and clean build tree before
 * testing
 */
BASE = 0xFFFF800000000000 + 0x100000 + 0x4000 + 0x8000;
/*           ^                  ^         ^        ^
 *           |                  |         |        |
 *     VIRTUAL_BASE         RESERVED     HOLE    STACK
 */

ALIGNMENT = 16;
PAGE_SIZE = 4096;

SECTIONS {
	. = BASE;
	__ld_image_start = .;

	.text : {
		*(.text .text.*)
		. = ALIGN(ALIGNMENT);
	}

	. = ALIGN(PAGE_SIZE);
	__ld_executable_end = .;

	.rodata : {
		*(.rodata .rodata.*);
		. = ALIGN(ALIGNMENT);
		
		__ld_start_ctors = .;
		*(.ctors)
		__ld_end_ctors = .;
		. = ALIGN(ALIGNMENT);
		
		__ld_start_dtors = .;
		*(.dtors)
		__ld_end_dtors = .;
		. = ALIGN(ALIGNMENT);
	}

	. = ALIGN(PAGE_SIZE);
	__ld_readonly_end = .;

	.data : {
		*(.data .data.*);
		. = ALIGN(ALIGNMENT);
	}

	.bss : {
		*(.bss .bss.*)
	}

	. = ALIGN(PAGE_SIZE);
	__ld_image_end = .;

	.lto : {
		*(.gnu.lto*)
	}

	/DISCARD/ : {
		*(.comment)
	}
}
