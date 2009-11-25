#ifndef __WONTON_KERNEL_SPIN_LOCK_H_INCLUDED__
#define __WONTON_KERNEL_SPIN_LOCK_H_INCLUDED__

#include <base/type.h>

namespace kernel {

class SpinLock {
public:
	SpinLock() : data(0) {}

	void lock();
	void unlock();

private:
	volatile base::Address data;
};

}

#endif
