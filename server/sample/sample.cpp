#include <jelly/SystemCall.h>
#include <kernel/abi.h>

using namespace jelly;
using namespace kernel;

int main() {
	int value = SystemCall<SYSCALL_RETURN_VALUE>::call();
	return value;
}
