#ifndef KERNEL_GENERIC_MEMORY_H_INCLUDED
#define KERNEL_GENERIC_MEMORY_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class Memory {
public:
	/**
	 * Similar to memcpy() in standard C library, except that this function returns void
	 */
	static void memcpy(void* dst, const void* src, Size size);

	/**
	 * !!! Attention, return value of this function is different from strcpy() in standard
	 * C library.
	 *
	 * @return Return the length of the copied string
	 */
	static Size strcpy(char* dst, const char* src);

	static void memset(void* dst, char value, Size count);

	static void zeroize(void* dst, Size size);

	static int strcmp(const char* first, const char* second);
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_MEMORY_H_INCLUDED */
