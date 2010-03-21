#include "SystemCallRouter.h"
#include "Message.h"
#include <kernel/abi.h>
#include "SystemService.h"

namespace kernel {

SystemCallRouter::Service SystemCallRouter::table[] = {
	(SystemCallRouter::Service)(SystemService<SYSCALL_EXIT_PROCESS>::serve),
	(SystemCallRouter::Service)(SystemService<SYSCALL_RETURN_VALUE>::serve)
};

int SystemCallRouter::route(int routine, U64 p1, U64 p2, U64 p3, U64 p4) {
	if (routine < (int)SYSCALL_MIN || routine > (int)SYSCALL_MAX) {
		Message::brief << "Unknown system call: " << routine << "\n";
		for (;;)
			;
	}
	return (table[routine])(p1, p2, p3, p4);
}

} // namespace kernel
