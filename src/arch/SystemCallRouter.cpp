#include "SystemCallRouter.h"
#include "Message.h"

namespace kernel {

void SystemCallRouter::route(int, U64 ret, Address, U64, U64, U64) {
	int returnValue = (int)ret;
	Message::brief << "Value Returned: " << returnValue << "\n";
	for (;;)
		;
}

} // namespace kernel
