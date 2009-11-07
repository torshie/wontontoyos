#ifndef __WONTON_KERNEL_TYPE_H_INCLUDED__
#define __WONTON_KERNEL_TYPE_H_INCLUDED__

#include <sexy/TERNARY.h>

namespace kernel {

typedef signed char I8;
typedef short I16;
typedef int I32;
typedef sexy::TERNARY<sizeof(long) == 8, long, long long>::T I64;

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef sexy::TERNARY<sizeof(unsigned long) == 8, unsigned long,
		unsigned long long>::T U64;

/**
 * Find some material on advanced C++ template usage.
 */
typedef sexy::TERNARY<sizeof(int) == sizeof(void*),
			unsigned int,
			sexy::TERNARY<sizeof(long) == sizeof(void*),
				unsigned long,
				sexy::TERNARY<sizeof(long long) == sizeof(void*),
					unsigned long long,
					void
				>::T
			>::T
		>::T Address;

typedef unsigned long long Size;
typedef Address Offset;

}

#endif
