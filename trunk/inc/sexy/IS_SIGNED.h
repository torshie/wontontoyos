#ifndef KERNEL_SEXY_IS_SIGNED_H_INCLUDED
#define KERNEL_SEXY_IS_SIGNED_H_INCLUDED

#include <generic/STATIC_ASSERT.h>

namespace kernel {

template<typename T>
class IS_SIGNED {
public:
	enum {
		value = 0
	};
};

#ifdef SPECIALIZE_IS_SIGNED_VALUE
#error "SPECIALIZE_IS_SIGNED_VALUE is already defined"
#else
#define SPECIALIZE_IS_SIGNED_VALUE(type) \
	template<> \
	class IS_SIGNED<type> { \
	public: \
		enum { \
			value = 1 \
		}; \
	}
#endif

SPECIALIZE_IS_SIGNED_VALUE(signed char);
SPECIALIZE_IS_SIGNED_VALUE(short);
SPECIALIZE_IS_SIGNED_VALUE(int);
SPECIALIZE_IS_SIGNED_VALUE(long);
SPECIALIZE_IS_SIGNED_VALUE(long long);

#undef SPECIALIZE_IS_SIGNED_VALUE

STATIC_ASSERT_TRUE(IS_SIGNED<signed char>::value)
STATIC_ASSERT_TRUE(IS_SIGNED<short>::value)
STATIC_ASSERT_TRUE(IS_SIGNED<int>::value)
STATIC_ASSERT_TRUE(IS_SIGNED<long>::value)
STATIC_ASSERT_TRUE(IS_SIGNED<long long>::value)
STATIC_ASSERT_FALSE(IS_SIGNED<unsigned char>::value)
STATIC_ASSERT_FALSE(IS_SIGNED<unsigned int>::value)
STATIC_ASSERT_FALSE(IS_SIGNED<unsigned short>::value)
STATIC_ASSERT_FALSE(IS_SIGNED<unsigned long>::value)
STATIC_ASSERT_FALSE(IS_SIGNED<unsigned long long>::value)
STATIC_ASSERT_FALSE(IS_SIGNED<void>::value)
STATIC_ASSERT_FALSE(IS_SIGNED<char*>::value)

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_SIGNED_H_INCLUDED */
