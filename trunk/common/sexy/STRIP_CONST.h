#ifndef KERNE_SEXY_STRIP_CONST_H_INCLUDED
#define KERNE_SEXY_STRIP_CONST_H_INCLUDED

#include "SAME_TYPE.h"

namespace kernel {

template<typename T> class STRIP_CONST {
public:
	typedef T Type;
};

template<typename T> class STRIP_CONST<const T> {
public:
	typedef T Type;
};

STATIC_ASSERT_TRUE((SAME_TYPE<int, STRIP_CONST<const int>::Type >::value));
STATIC_ASSERT_TRUE((SAME_TYPE<int, STRIP_CONST<int>::Type >::value));

} // namespace kernel

#endif // KERNE_SEXY_STRIP_CONST_H_INCLUDED
