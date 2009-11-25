#include <kernel/arch/SpinLock.h>

namespace kernel {

using namespace base;

void SpinLock::lock() {
	register Address ticket = 1;
	do {
		asm volatile("lock xchg %0, %1" : "=r"(ticket), "=m"(data));
	} while (ticket);
}

void SpinLock::unlock() {
	data = 0;
}

}
