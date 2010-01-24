#ifndef KERNEL_ARCH_SPIN_LOCK_H_INCLUDED
#define KERNEL_ARCH_SPIN_LOCK_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class SpinLock {
public:
	SpinLock() : data(0) {}

	void lock();
	void unlock();

private:
	volatile Address data;
};

} /* namespace kernel */

#endif /* KERNEL_ARCH_SPIN_LOCK_H_INCLUDED */
