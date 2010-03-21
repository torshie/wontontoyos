#ifndef KERNEL_SEXY_IS_POINTER_H_INCLUDED
#define KERNEL_SEXY_IS_POINTER_H_INCLUDED

#include <sexy/IS_POINTER_TO_MEMBER.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

template<typename T> class IS_POINTER {
public:
	enum {
		value = 0 | IS_POINTER_TO_MEMBER<T>::value
	};
};

template<typename T> class IS_POINTER<T*> {
public:
	enum {
		value = 1
	};
};


template<typename T> class IS_POINTER<T const> {
public:
	enum {
		value = IS_POINTER<T>::value
	};
};

STATIC_ASSERT_TRUE(IS_POINTER<void*>::value)
STATIC_ASSERT_TRUE(IS_POINTER<void* const>::value)
STATIC_ASSERT_TRUE(IS_POINTER<void**>::value)
STATIC_ASSERT_TRUE(IS_POINTER<void (*)(void)>::value)
STATIC_ASSERT_TRUE(IS_POINTER<void (IS_POINTER<void>::*)(void)>::value)
STATIC_ASSERT_FALSE(IS_POINTER<void>::value)
STATIC_ASSERT_FALSE(IS_POINTER<char&>::value)

} // namespace kernel

#endif // KERNEL_SEXY_IS_POINTER_H_INCLUDED
