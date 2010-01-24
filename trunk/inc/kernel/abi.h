#ifndef KERNEL_ABI_H_INCLUDED
#define KERNEL_ABI_H_INCLUDED

/**
 * !!!!!!!!!!!!!!!
 * !!! Warning !!!
 * !!!!!!!!!!!!!!!
 * If you want to change variables in this file, make sure you have also
 * changed the corresponding linker scripts.
 */

#ifndef __ASM__
namespace kernel {
enum {
#endif

#ifndef __ASM__
	KERNEL_VIRTUAL_BASE = 0xFFFFFF0000000000,
	KERNEL_LOAD_ADDRESS = 0x105000,
#else
#	define KERNEL_VIRTUAL_BASE 0xFFFFFF0000000000
#	define KERNEL_LOAD_ADDRESS 0x105000
#endif

#ifndef __ASM__
}; /* enum */
} /* namespace kernel */
#endif

#endif /* KERNEL_ABI_H_INCLUDED */
