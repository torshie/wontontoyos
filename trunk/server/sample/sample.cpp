#include <jelly/SystemCall.h>
#include <kernel/abi.h>

using namespace jelly;
using namespace kernel;

int main() {
	SystemCall<SYSCALL_PRINT>::call(10);
	for (;;);
	return 20;
}
