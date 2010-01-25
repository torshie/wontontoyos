#ifndef KERNEL_SEXY_ASSIGN_ZERO_INITIALIZER_H_INCLUDED
#define KERNEL_SEXY_ASSIGN_ZERO_INITIALIZER_H_INCLUDED

namespace kernel {

class ASSIGN_ZERO_INITIALIZER {
public:
	template<typename T>
	static void initialize(T& v) {
		v = 0;
	}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_ASSIGN_ZERO_INITIALIZER_H_INCLUDED */
