#ifndef KERNEL_SEXY_NULL_INITIALIZER_H_INCLUDED
#define KERNEL_SEXY_NULL_INITIALIZER_H_INCLUDED

namespace kernel {

class NULL_INITIALIZER {
public:
	template<typename T>
	static void initialize(T&) {}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_NULL_INITIALIZER_H_INCLUDED */
