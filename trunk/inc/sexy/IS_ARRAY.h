#ifndef KERNEL_SEXY_TEMPLATE_IS_ARRAY_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_IS_ARRAY_H_INCLUDED

#include <generic/type.h>

namespace kernel {

template<typename T> class IS_ARRAY {
public:
	enum {
		value = 0
	};
};

template<typename T, U64 N> class IS_ARRAY<T[N]> {
public:
	enum {
		value = 1
	};
};

template<typename T> class IS_ARRAY<T[]> {
public:
	enum {
		value = 1
	};
};

template<typename T> class IS_ARRAY<T[0]> {
public:
	enum {
		value = 1
	};
};

STATIC_ASSERT_FALSE(IS_ARRAY<void>::value)
STATIC_ASSERT_FALSE(IS_ARRAY<char>::value)
STATIC_ASSERT_FALSE(IS_ARRAY<char*>::value)
STATIC_ASSERT_TRUE(IS_ARRAY<char[]>::value)
STATIC_ASSERT_TRUE(IS_ARRAY<char[1]>::value)
STATIC_ASSERT_TRUE(IS_ARRAY<char[0]>::value)

} /* namespace kernel */

#endif /* KERNEL_SEXY_TEMPLATE_IS_ARRAY_H_INCLUDED */
