#include <jelly/SystemCall.h>
#include <kernel/abi.h>

using namespace jelly;
using namespace kernel;

int main() {
	int value = SystemCall<SYSCALL_SUM>::call(1, 2, 3, 4);
	return value;
}
