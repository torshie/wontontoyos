#ifndef KERNEL_SEXY_IS_POINTER_H_INCLUDED
#define KERNEL_SEXY_IS_POINTER_H_INCLUDED

#include <sexy/IS_POINTER_TO_MEMBER.h>

namespace kernel {

template<typename T>
class IS_POINTER {
public:
	enum {
		value = 0 | IS_POINTER_TO_MEMBER<T>::value
	};
};

template<typename T>
class IS_POINTER<T*> {
public:
	enum {
		value = 1
	};
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_POINTER_H_INCLUDED */
