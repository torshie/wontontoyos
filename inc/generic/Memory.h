#ifndef KERNEL_GENERIC_MEMORY_H_INCLUDED
#define KERNEL_GENERIC_MEMORY_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class Memory {
public:
	/**
	 * Memory copy
	 * Similar to memcpy() in standard C library, except that this
	 * function returns void
	 */
	static void memcpy(void* dst, const void* src, Size size);

	/**
	 * Copy a C-style string.
	 *
	 * !!! Attention, return value of this function is different from
	 * strcpy() in standard C library.
	 *
	 * @return Return the length of the copied string
	 */
	static int strcpy(char* dst, const char* src);

	/**
	 * Set a memory area to a given value
	 */
	static void memset(void* dst, char value, Size count);

	/**
	 * Set a memory area to zero
	 *
	 * @param dst The base address of the memory
	 * @param size The size of the memory in bytes
	 */
	static void zeroize(void* dst, Size size);
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_MEMORY_H_INCLUDED */
