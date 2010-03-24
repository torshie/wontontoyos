#include "Thread.h"
#include "arch/Processor.h"

namespace kernel {

void Thread::start() {
	Processor& processor = getProcessorInstance<Processor>();
	processor.enterUserMode(entry);
	for (;;);
}

} // namespace kernel
