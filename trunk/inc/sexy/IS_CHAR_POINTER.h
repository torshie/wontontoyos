#ifndef KERNEL_SEXY_IS_CHAR_POINTER_H_INCLUDED
#define KERNEL_SEXY_IS_CHAR_POINTER_H_INCLUDED

namespace kernel {
template<typename T>
class IS_CHAR_POINTER {
public:
	enum {
		value = 0
	};
};

template<>
class IS_CHAR_POINTER<char*> {
public:
	enum {
		value = 1
	};
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_CHAR_POINTER_H_INCLUDED */
