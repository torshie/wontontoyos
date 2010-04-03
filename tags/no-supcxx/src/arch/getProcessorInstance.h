#ifndef KERNEL_ARCH_GET_PROCESSOR_INSTANCE_H_INCLUDED
#define KERNEL_ARCH_GET_PROCESSOR_INSTANCE_H_INCLUDED

namespace kernel {

// XXX Improve this function
template<typename T> T& getProcessorInstance() {
	static T instance;
	return instance;
}

} // namespace kernel

#endif // KERNEL_ARCH_GET_PROCESSOR_INSTANCE_H_INCLUDED
