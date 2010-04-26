OUTPUT_ARCH(i386:x86-64)
OUTPUT_FORMAT(elf64-x86-64)
ENTRY (_start)

/* Modify pangu.ld if this value is modified */
BASE = 0x600000 - 0x2000;

ALIGNMENT = 8;

SECTIONS{
	. = BASE;

	__ld_image_start = .;
	.text : AT(ADDR(.text) - BASE) {
		*(.text .text.*)
		. = ALIGN(ALIGNMENT);
	}

	.rodata : AT(ADDR(.rodata) - BASE) {
		*(.rodata .rodata.*)
		. = ALIGN(ALIGNMENT);

		__ld_start_ctors = .;
		*(.ctors*)
		__ld_end_ctors = .;
		. = ALIGN(ALIGNMENT);
 
		*(.dtors*)
		. = ALIGN(ALIGNMENT);
	}

	.data : AT(ADDR(.data) - BASE) {
		*(.data .data.*)
		. = ALIGN(ALIGNMENT);
	}

	.bss : AT(ADDR(.bss) - BASE) {
		*(.bss .bss.*)
	}

	.lto : {
		*(.gnu.lto*)
	}

	/DISCARD/ : {
		*(.comment)
	}
}
