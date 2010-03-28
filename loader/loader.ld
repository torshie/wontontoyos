OUTPUT_ARCH(i386:x86-64)
OUTPUT_FORMAT(elf64-x86-64)
ENTRY (_start)

/* Modify pangu.S as well if this value is modified */
BASE = 0x200000 - 0x1000;

ALIGNMENT = 8;

SECTIONS{
	. = BASE;
	__ld_kernel_stack__ = . - ALIGNMENT;

	.text : AT(ADDR(.text) - BASE) {
		__ld_code_start__ = .;
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
		__ld_data_end__ = .;
	}

	.bss : AT(ADDR(.bss) - BASE) {
		*(.bss .bss.*)
	}

	__ld_bss_end__ = ALIGN(4096);
	
	.lto : {
		*(.gnu.lto*)
	}

	/DISCARD/ : {
		*(.comment)
		*(.eh_frame)
	}
}
