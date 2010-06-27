#ifndef KERNEL_SEXY_SAME_TYPE_H_INCLUDED
#define KERNEL_SEXY_SAME_TYPE_H_INCLUDED

#include <sexy/STATIC_ASSERT.h>

namespace kernel {

template<typename A, typename B> class SAME_TYPE {
public:
	enum {
		value = 0
	};
};

template<typename T> class SAME_TYPE<T, T> {
public:
	enum {
		value = 1
	};
};

STATIC_ASSERT_TRUE((SAME_TYPE<int, int>::value));
STATIC_ASSERT_FALSE((SAME_TYPE<int, char>::value));
STATIC_ASSERT_FALSE((SAME_TYPE<int, const int>::value));
STATIC_ASSERT_FALSE((SAME_TYPE<int, volatile int>::value));

} // namespace kernel

#endif // KERNEL_SEXY_SAME_TYPE_H_INCLUDED
