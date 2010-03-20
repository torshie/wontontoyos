#include "Thread.h"
#include "arch/Processor.h"

namespace kernel {

void Thread::start() {
	Processor& processor = getSingleInstance<Processor>();
	processor.enterUserMode(entry);
	for (;;);
}

} // namespace kernel
