#ifndef KERNEL_SEXY_NAKED_H_INCLUDED
#define KERNEL_SEXY_NAKED_H_INCLUDED

#include "STRIP_CONST.h"
#include "STRIP_VOLATILE.h"
#include <generic/STATIC_ASSERT.h>

namespace kernel {

template<typename T> class NAKED {
public:
	typedef typename STRIP_CONST<typename STRIP_VOLATILE<T>::Type >::Type Type;
};

STATIC_ASSERT_TRUE((SAME_TYPE<int, NAKED<const int>::Type >::value));
STATIC_ASSERT_TRUE((SAME_TYPE<int, NAKED<volatile int>::Type >::value));
STATIC_ASSERT_TRUE((SAME_TYPE<int, NAKED<int>::Type >::value));

} // namespace kernel

#endif // KERNEL_SEXY_NAKED_H_INCLUDED
