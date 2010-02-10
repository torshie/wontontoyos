#ifndef KERNEL_GENERIC_GET_SINGLE_INSTANCE_H_INCLUDED
#define KERNEL_GENERIC_GET_SINGLE_INSTANCE_H_INCLUDED

namespace kernel {

/**
 * XXX Make this function thread-safe, although it already is when compiled with g++
 */
template<typename T>
T& getSingleInstance() {
	static T instance;
	return instance;
}

} /* namespace kernel */

#endif /* KERNEL_GENERIC_GET_SINGLE_INSTANCE_H_INCLUDED */
