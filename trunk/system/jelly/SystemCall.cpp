#include "SystemCall.h"
#include <kernel/abi.h>

using namespace kernel;

namespace jelly {

void SystemCall<SYSCALL_EXIT_PROCESS>::call(int status) {
	asm volatile ("syscall" : : "D"(SYSCALL_EXIT_PROCESS), "S"(status));
}

int SystemCall<SYSCALL_RETURN_VALUE>::call() {
	int ret;
	asm volatile ("syscall" : "=a"(ret) : "D"(SYSCALL_RETURN_VALUE));
	return ret;
}

} // namespace jelly
