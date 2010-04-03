#ifndef KERNEL_SEXY_IS_POINTER_TO_MEMBER_H_INCLUDED
#define KERNEL_SEXY_IS_POINTER_TO_MEMBER_H_INCLUDED

namespace kernel {

template<typename T> class IS_POINTER_TO_MEMBER {
public:
	enum {
		value = 0
	};
};

template<typename T, typename Class> class IS_POINTER_TO_MEMBER<T Class::*> {
public:
	enum {
		value = 1
	};
};

} // namespace kernel

#endif // KERNEL_SEXY_IS_POINTER_TO_MEMBER_H_INCLUDED
