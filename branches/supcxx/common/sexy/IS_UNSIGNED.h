#ifndef KERNEL_SEXY_IS_UNSIGNED_H_INCLUDED
#define KERNEL_SEXY_IS_UNSIGNED_H_INCLUDED

#include <sexy/IS_SIGNED.h>
#include <sexy/IS_INTEGER.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

template<typename T> class IS_UNSIGNED {
public:
	enum {
		value = IS_INTEGER<T>::value ? (!IS_SIGNED<T>::value) : 0
	};
};

STATIC_ASSERT_TRUE(IS_UNSIGNED<unsigned char>::value)
STATIC_ASSERT_TRUE(IS_UNSIGNED<unsigned int>::value)
STATIC_ASSERT_TRUE(IS_UNSIGNED<unsigned short>::value)
STATIC_ASSERT_TRUE(IS_UNSIGNED<unsigned long>::value)
STATIC_ASSERT_TRUE(IS_UNSIGNED<unsigned long long>::value)
STATIC_ASSERT_FALSE(IS_UNSIGNED<signed char>::value)
STATIC_ASSERT_FALSE(IS_UNSIGNED<short>::value)
STATIC_ASSERT_FALSE(IS_UNSIGNED<int>::value)
STATIC_ASSERT_FALSE(IS_UNSIGNED<long>::value)
STATIC_ASSERT_FALSE(IS_UNSIGNED<long long>::value)
STATIC_ASSERT_FALSE(IS_UNSIGNED<void>::value)

} // namespace kernel

#endif // KERNEL_SEXY_IS_UNSIGNED_H_INCLUDED
