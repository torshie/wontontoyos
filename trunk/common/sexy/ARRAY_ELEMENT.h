#ifndef KERNEL_SEXY_ARRAY_ELEMENT_H_INCLUDED
#define KERNEL_SEXY_ARRAY_ELEMENT_H_INCLUDED

#include <sexy/STATIC_ASSERT.h>
#include <sexy/SAME_TYPE.h>

namespace kernel {

template<typename T> class ARRAY_ELEMENT {
public:
	typedef void Type;
};

template<typename Element, Size N> class ARRAY_ELEMENT<Element[N]> {
public:
	typedef Element Type;
};

template<typename Element> class ARRAY_ELEMENT<Element[]> {
public:
	typedef Element Type;
};

template<typename Element> class ARRAY_ELEMENT<Element[0]> {
public:
	typedef Element Type;
};

STATIC_ASSERT_TRUE((SAME_TYPE<ARRAY_ELEMENT<char[3]>::Type, char>::value))
STATIC_ASSERT_TRUE((SAME_TYPE<ARRAY_ELEMENT<char[]>::Type, char>::value))
STATIC_ASSERT_TRUE((SAME_TYPE<ARRAY_ELEMENT<char[0]>::Type, char>::value))
STATIC_ASSERT_TRUE((SAME_TYPE<ARRAY_ELEMENT<char>::Type, void>::value))

} // namespace kernel

#endif
