OUTPUT_ARCH(i386:x86-64)
OUTPUT_FORMAT(elf64-x86-64)
ENTRY(start)

/* The second entry of the level four page map */
BASE = 0x8000000000;

ALIGNMENT = 16;
PAGE_SIZE = 4096;

SECTIONS {
	. = BASE;
	
	.init : {
		*(.init)
		. = ALIGN(ALIGNMENT);
	}

	.text : {
		*(.text .text.*)
		. = ALIGN(ALIGNMENT);
	}

	.rodata : {
		*(.rodata .rodata.*);
		. = ALIGN(ALIGNMENT);
	}

	.ctors : {
		*(.ctors)
		. = ALIGN(ALIGNMENT);
	}

	.dtors : {
		*(.dtors)
		. = ALIGN(ALIGNMENT);
	}

	.data : {
		*(.data .data.*);
		. = ALIGN(ALIGNMENT);
	}

	.bss : {
		*(.bss .bss.*)
	}

	. = ALIGN(PAGE_SIZE);
	__ld_image_end = .;

	/DISCARD/ : {
		*(.comment)
		*(.eh_frame)
	}
}
