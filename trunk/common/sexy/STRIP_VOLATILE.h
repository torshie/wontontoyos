#ifndef KERNEL_SEXY_STRIP_VOLATILE_H_INCLUDED
#define KERNEL_SEXY_STRIP_VOLATILE_H_INCLUDED

#include <sexy/SAME_TYPE.h>

namespace kernel {

template<typename T> class STRIP_VOLATILE {
public:
	typedef T Type;
};

template<typename T> class STRIP_VOLATILE<volatile T> {
public:
	typedef T Type;
};

STATIC_ASSERT_TRUE((SAME_TYPE<int, STRIP_VOLATILE<volatile int>::Type >::value));
STATIC_ASSERT_TRUE((SAME_TYPE<int, STRIP_VOLATILE<int>::Type >::value));

} // namespace kernel

#endif // KERNEL_SEXY_STRIP_VOLATILE_H_INCLUDED
