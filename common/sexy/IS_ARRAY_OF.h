#ifndef KERNEL_SEXY_TEMPLATE_IS_ARRAY_OF_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_IS_ARRAY_OF_H_INCLUDED

#include <generic/type.h>
#include <sexy/STATIC_ASSERT.h>

namespace kernel {

template<typename Array, typename Element> class IS_ARRAY_OF {
public:
	enum {
		value = 0
	};
};

template<typename Element, Size N> class IS_ARRAY_OF<Element[N], Element> {
public:
	enum {
		value = 1
	};
};

template<typename Element> class IS_ARRAY_OF<Element[], Element> {
public:
	enum {
		value = 1
	};
};

template<typename Element> class IS_ARRAY_OF<Element[0], Element> {
public:
	enum {
		value = 1
	};
};

STATIC_ASSERT_TRUE((IS_ARRAY_OF<char[], char>::value))
STATIC_ASSERT_TRUE((IS_ARRAY_OF<char[1], char>::value))
STATIC_ASSERT_TRUE((IS_ARRAY_OF<char[0], char>::value))
STATIC_ASSERT_FALSE((IS_ARRAY_OF<int[1], char>::value))

} // namespace kernel

#endif
