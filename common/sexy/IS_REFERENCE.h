#ifndef KERNEL_SEXY_IS_REFERENCE_H_INCLUDED
#define KERNEL_SEXY_IS_REFERENCE_H_INCLUDED

#include <sexy/STATIC_ASSERT.h>

namespace kernel {

template<typename T> class IS_REFERENCE {
public:
	enum {
		value = 0
	};
};

template<typename T> class IS_REFERENCE<T&> {
public:
	enum {
		value = 1
	};
};

STATIC_ASSERT_TRUE(IS_REFERENCE<char&>::value)
STATIC_ASSERT_FALSE(IS_REFERENCE<char>::value)

} // namespace kernel

#endif // KERNEL_SEXY_IS_REFERENCE_H_INCLUDED
