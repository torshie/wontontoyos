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

int SystemCall<SYSCALL_PRINT>::call(int input) {
	int ret;
	asm volatile ("syscall" : "=a"(ret) : "D"(SYSCALL_PRINT), "S"(input));
	return ret;
}

int SystemCall<SYSCALL_SUM>::call(int a, int b, int c, int d) {
	int ret;
	asm volatile(
			"mov %4, %%r8\n"
			"mov %5, %%r9\n"
			"syscall" : "=a"(ret) : "D"(SYSCALL_SUM), "S"(a), "d"(b), "g"(c), "g"(d));
	return ret;
}

} // namespace jelly
