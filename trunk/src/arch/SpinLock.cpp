#include "SpinLock.h"

namespace kernel {

void SpinLock::lock() {
	register Address ticket = 1;
	do {
		asm volatile("lock xchg %0, %1" : "=r"(ticket), "=m"(data));
	} while (ticket);
}

void SpinLock::unlock() {
	data = 0;
}

} /* namespace kernel */
