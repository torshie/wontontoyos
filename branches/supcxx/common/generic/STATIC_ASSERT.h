#ifndef KERNEL_GENERIC_STATIC_ASSERT_H_INCLUDED
#define KERNEL_GENERIC_STATIC_ASSERT_H_INCLUDED

#define STATIC_ASSERT_TRUE(expression) \
	namespace internal { \
		typedef int __staticAssert__[(expression) ? 1 : -1]; \
	}

#define STATIC_ASSERT_FALSE(expression) \
	namespace internal { \
		typedef int __staticAssert__[!(expression) ? 1 : -1]; \
	}

#define STATIC_ASSERT_EQUAL(first, second) \
	namespace internal { \
		typedef int __staticAssert__[(first) == (second) ? 1 : -1]; \
	}

#define STATIC_ASSERT_UNEQUAL(first, second) \
	namespace internal { \
		typedef int __staticAssert__[(first) != (second) ? 1 : -1]; \
	}

#endif // KERNEL_GENERIC_STATIC_ASSERT_H_INCLUDED
