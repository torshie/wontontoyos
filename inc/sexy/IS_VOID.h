#ifndef KERNEL_SEXY_IS_VOID_H_INCLUDED
#define KERNEL_SEXY_IS_VOID_H_INCLUDED

namespace kernel {

template<typename T>
class IS_VOID {
public:
	enum {
		value = 0
	};
};

template<>
class IS_VOID<void> {
public:
	enum {
		value = 1
	};
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_VOID_H_INCLUDED */
