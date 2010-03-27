#include "Thread.h"

namespace kernel {

void Thread::start() {
	asm volatile("mov $0x200, %%r11\n"
			"sysretq" : : "c"(entry));
	for (;;);
}

} // namespace kernel
