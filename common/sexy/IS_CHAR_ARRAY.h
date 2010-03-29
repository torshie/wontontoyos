#ifndef KERNEL_SEXY_IS_CHAR_ARRAY_H_INCLUDED
#define KERNEL_SEXY_IS_CHAR_ARRAY_H_INCLUDED

#include "NAKED.h"

namespace kernel {

template<typename T> class IS_CHAR_ARRAY {
public:
	enum {
		value = 0
	};
};

template<typename T, int N> class IS_CHAR_ARRAY<T[N]> {
public:
	enum {
		value = SAME_TYPE<char, typename NAKED<T>::Type >::value
	};
};

STATIC_ASSERT_TRUE(IS_CHAR_ARRAY<char[1]>::value);
STATIC_ASSERT_TRUE(IS_CHAR_ARRAY<const char[1]>::value);
STATIC_ASSERT_TRUE(IS_CHAR_ARRAY<volatile char[1]>::value);
STATIC_ASSERT_FALSE(IS_CHAR_ARRAY<char[]>::value);
STATIC_ASSERT_FALSE(IS_CHAR_ARRAY<char>::value);
STATIC_ASSERT_FALSE(IS_CHAR_ARRAY<char*>::value);
STATIC_ASSERT_FALSE(IS_CHAR_ARRAY<const char*>::value);
STATIC_ASSERT_FALSE(IS_CHAR_ARRAY<volatile char *>::value);
STATIC_ASSERT_FALSE(IS_CHAR_ARRAY<int[2]>::value);
STATIC_ASSERT_FALSE(IS_CHAR_ARRAY<unsigned char[1]>::value);

} // namespace kernel

#endif // KERNEL_SEXY_IS_CHAR_ARRAY_H_INCLUDED
