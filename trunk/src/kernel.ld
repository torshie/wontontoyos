OUTPUT_ARCH(i386:x86-64)
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

/**
 * !!!!!!!!!!!!!!!
 * !!! Warning !!!
 * !!!!!!!!!!!!!!!
 * If you want to change load address, make sure you have changed <kernel/abi.h>
 */
BASE = 0xFFFF800000000000 + 0x100000 + 0xA000 + 0x6000;
/*           ^                  ^         ^        ^
 *           |                  |         |        |
 *     VIRTUAL_BASE         RESERVED  TEMP_AREA  STACK
 */

ALIGNMENT = 16;
PAGE_SIZE = 4096;

SECTIONS {
	. = BASE;
	__ld_image_start = .;
	
	.init : {
		*(.init)
		. = ALIGN(ALIGNMENT);
	}

	.text : {
		*(.text .text.*)
		. = ALIGN(ALIGNMENT);
	}

	. = ALIGN(PAGE_SIZE);
	__ld_executable_end = .;

	.rodata : {
		*(.rodata .rodata.*);
		. = ALIGN(ALIGNMENT);
	}

	.ctors : {
		__ld_start_ctors = .;
		*(.ctors)
		__ld_end_ctors = .;
		. = ALIGN(ALIGNMENT);
	}

	.dtors : {
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
	__ld_bss_end = .;

/*	/DISCARD/ : {
		*(.comment)
	} */
}
