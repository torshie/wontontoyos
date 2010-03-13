#ifndef KERNEL_GENERIC_UTILS_H_INCLUDED
#define KERNEL_GENERIC_UTILS_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class Utils {
public:
	static void memcpy(void* dst, const void* src, Size size);
	static Size strncpy(char* dst, const char* src, Size space);
	static void memset(void* dst, char value, Size count);
	static void zeroize(void* dst, Size size);
	static int strcmp(const char* first, const char* second);
	static Size strlen(const char* string);
	static const char* basename(const char* path);
	static U64 ceilingDivide(U64 value, U64 round);
	static Size roundUp(Size size, Size round);
	static Size roundDown(Size size, Size round);
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_UTILS_H_INCLUDED */
