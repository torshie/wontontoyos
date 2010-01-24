#ifndef KERNEL_GENERIC_TYPE_H_INCLUDED
#define KERNEL_GENERIC_TYPE_H_INCLUDED

#include <sexy/TERNARY.h>

namespace kernel {

typedef signed char I8;
typedef short I16;
typedef int I32;
typedef TERNARY<sizeof(long) == 8, long, long long>::T I64;

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef TERNARY<sizeof(unsigned long) == 8, unsigned long,
		unsigned long long>::T U64;

/**
 * If you find it difficult to read the following lines, find some
 * advanced material on C++ template.
 */
typedef TERNARY<sizeof(int) == sizeof(void*),
			unsigned int,
			TERNARY<sizeof(long) == sizeof(void*),
				unsigned long,
				TERNARY<sizeof(long long) == sizeof(void*),
					unsigned long long,
					void
				>::T
			>::T
		>::T Address;

typedef unsigned long long Size;
typedef Address Offset;

} /* namespace kernel */

#endif /* KERNEL_GENERIC_TYPE_H_INCLUDED */
