#ifndef KERNEL_SEXY_IS_ENUM_H_INCLUDED
#define KERNEL_SEXY_IS_ENUM_H_INCLUDED

#include <sexy/IS_POINTER.h>
#include <sexy/IS_REFERENCE.h>
#include <sexy/IS_INTEGER.h>
#include <sexy/IS_VOID.h>
#include <sexy/IS_ARRAY.h>
#include <sexy/IS_CLASS.h>
#include <sexy/IS_BOOL.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

template<typename T> class IS_ENUM {
public:
	enum {
		value = !(IS_POINTER<T>::value || IS_REFERENCE<T>::value || IS_INTEGER<T>::value
						|| IS_VOID<T>::value || IS_ARRAY<T>::value || IS_CLASS<T>::value
						|| IS_BOOL<T>::value)
	};
};

STATIC_ASSERT_FALSE(IS_ENUM<bool>::value);

} // namespace kernel

#endif // KERNEL_SEXY_IS_ENUM_H_INCLUDED
