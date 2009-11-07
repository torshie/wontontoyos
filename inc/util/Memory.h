#ifndef __WONTON_UTIL_MEMORY_H_INCLUDED__
#define __WONTON_UTIL_MEMORY_H_INCLUDED__

#include <kernel/type.h>

namespace util {

class Memory {
public:
	/**
	 * Memory copy
	 * Similar to memcpy() in standard C library, except that this
	 * function returns void
	 */
	static void memcpy(void* dst, const void* src, kernel::Size size);

	/**
	 * Copy a C-style string.
	 * !!! Attention, return value of this function is different from
	 * strcpy() in standard C library.
	 *
	 * @return Return the length of the copied string
	 */
	static int strcpy(char* dst, const char* src);

	/**
	 * Set a memory area to a given value
	 */
	static void memset(void* dst, char value, kernel::Size count);

	/**
	 * Set a memory area to zero
	 *
	 * @param dst The base address of the memory
	 * @param size The size of the memory in bytes
	 */
	static void zeroize(void* dst, kernel::Size size);
};

}

#endif
