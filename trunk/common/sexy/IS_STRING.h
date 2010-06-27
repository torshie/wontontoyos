#ifndef KERNEL_SEXY_IS_STRING_H_INCLUDED
#define KERNEL_SEXY_IS_STRING_H_INCLUDED

#include <sexy/STATIC_ASSERT.h>

namespace kernel {

template<typename T> class IS_STRING {
public:
	enum {
		value = 0
	};
};

template<typename T> class IS_STRING<T&> {
public:
	enum {
		value = IS_STRING<T>::value
	};
};

template<typename T> class IS_STRING<const T> {
public:
	enum {
		value = IS_STRING<T>::value
	};
};

#ifdef SPECIALIZE_IS_STRING_VALUE
#	error "SPECIALIZE_IS_STRING_VALUE is already defined"
#else
#	define SPECIALIZE_IS_STRING_VALUE(type) \
		template<> class IS_STRING<type> { \
		public: \
			enum { \
				value = 1 \
			}; \
		};
#endif

SPECIALIZE_IS_STRING_VALUE(char*)
SPECIALIZE_IS_STRING_VALUE(const char*)
SPECIALIZE_IS_STRING_VALUE(char[])
SPECIALIZE_IS_STRING_VALUE(const char[])

template<int SIZE> class IS_STRING<char[SIZE]> {
public:
	enum {
		value = 1
	};
};

template<int SIZE> class IS_STRING<const char[SIZE]> {
public:
	enum {
		value = 1
	};
};

#undef SPECIALIZE_IS_STRING_VALUE

STATIC_ASSERT_TRUE(IS_STRING<char*>::value)
STATIC_ASSERT_TRUE(IS_STRING<char*&>::value)
STATIC_ASSERT_TRUE(IS_STRING<const char*>::value)
STATIC_ASSERT_TRUE(IS_STRING<const char*&>::value)
STATIC_ASSERT_TRUE(IS_STRING<char[1]>::value)
STATIC_ASSERT_TRUE(IS_STRING<const char[1]>::value)
STATIC_ASSERT_TRUE(IS_STRING<char* const>::value)
STATIC_ASSERT_TRUE(IS_STRING<char* const &>::value)
STATIC_ASSERT_TRUE(IS_STRING<const char* const>::value)
STATIC_ASSERT_TRUE(IS_STRING<const char* const &>::value)
STATIC_ASSERT_TRUE(IS_STRING<char[]>::value)
STATIC_ASSERT_TRUE(IS_STRING<const char[]>::value)
STATIC_ASSERT_FALSE(IS_STRING<void>::value)
STATIC_ASSERT_FALSE(IS_STRING<char>::value)
STATIC_ASSERT_FALSE(IS_STRING<char**>::value)
STATIC_ASSERT_FALSE(IS_STRING<char*[]>::value)

} // namespace kernel

#endif // KERNEL_SEXY_IS_STRING_H_INCLUDED
