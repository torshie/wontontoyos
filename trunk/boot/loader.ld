OUTPUT_ARCH(i386:x86-64)
OUTPUT_FORMAT(elf64-x86-64)
ENTRY (_start)

BASE = 0x180000;

ALIGNMENT = 8;

SECTIONS{
	. = BASE;
	__ld_kernel_stack__ = . - ALIGNMENT;

	.text : AT(ADDR(.text) - BASE) {
		__ld_code_start__ = .;
		*(.text)
		. = ALIGN(ALIGNMENT);
	}
	
	.rodata : AT(ADDR(.rodata) - BASE) {
		*(.rodata*)
		. = ALIGN(ALIGNMENT);
		__ld_start_ctors = .;
		*(.ctors*)
		__ld_end_ctors = .;
		. = ALIGN(ALIGNMENT); 
		*(.dtors*)
		. = ALIGN(ALIGNMENT);
	}

	.data : AT(ADDR(.data) - BASE) {
		*(.data)
		. = ALIGN(ALIGNMENT);
		__ld_data_end__ = .;
	}

	.bss : AT(ADDR(.bss) - BASE) {
		*(.bss)
	}

	__ld_bss_end__ = ALIGN(4096);

	/DISCARD/ : {
		*(.comment)
		*(.eh_frame)
	}
}
