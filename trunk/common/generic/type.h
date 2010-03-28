#ifndef KERNEL_GENERIC_TYPE_H_INCLUDED
#define KERNEL_GENERIC_TYPE_H_INCLUDED

#include <sexy/TYPE_SELECTOR.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

typedef signed char I8;
typedef short I16;

typedef int I32;
typedef TYPE_SELECTOR<sizeof(long) == 8, long, long long>::Type I64;

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef TYPE_SELECTOR<sizeof(unsigned long) == 8, unsigned long, unsigned long long>::Type U64;

typedef TYPE_SELECTOR<sizeof(int) == sizeof(void*),
			unsigned int,
			TYPE_SELECTOR<sizeof(long) == sizeof(void*),
				unsigned long,
				TYPE_SELECTOR<sizeof(long long) == sizeof(void*),
					unsigned long long,
					void
				>::Type
			>::Type
		>::Type Address;

typedef TYPE_SELECTOR<sizeof(int) == sizeof(long), unsigned int, unsigned long>::Type Size;
typedef Address Offset;
typedef long NativeInteger;
typedef unsigned long NativeUnsigned;

STATIC_ASSERT_EQUAL(sizeof(I8), 1)
STATIC_ASSERT_EQUAL(sizeof(U8), 1)
STATIC_ASSERT_EQUAL(sizeof(I16), 2)
STATIC_ASSERT_EQUAL(sizeof(U16), 2)
STATIC_ASSERT_EQUAL(sizeof(I32), 4)
STATIC_ASSERT_EQUAL(sizeof(U32), 4)
STATIC_ASSERT_EQUAL(sizeof(I64), 8)
STATIC_ASSERT_EQUAL(sizeof(U64), 8)
STATIC_ASSERT_EQUAL(sizeof(void*), sizeof(Address))

} // namespace kernel

#endif // KERNEL_GENERIC_TYPE_H_INCLUDED
