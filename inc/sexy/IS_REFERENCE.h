#ifndef KERNEL_SEXY_IS_REFERENCE_H_INCLUDED
#define KERNEL_SEXY_IS_REFERENCE_H_INCLUDED

namespace kernel {

template<typename T>
class IS_REFERENCE {
public:
	enum {
		value = 0
	};
};

template<typename T>
class IS_REFERENCE<T&> {
public:
	enum {
		value = 1
	};
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_REFERENCE_H_INCLUDED */
