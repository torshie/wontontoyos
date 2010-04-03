#include "ServiceRouter.h"
#include "Message.h"
#include <kernel/abi.h>
#include "SystemService.h"

namespace kernel {

ServiceRouter::Service ServiceRouter::table[] = {
	(ServiceRouter::Service)(SystemService<SYSCALL_EXIT_PROCESS>::serve),
	(ServiceRouter::Service)(SystemService<SYSCALL_RETURN_VALUE>::serve),
	(ServiceRouter::Service)(SystemService<SYSCALL_PRINT>::serve),
	(ServiceRouter::Service)(SystemService<SYSCALL_SLEEP>::serve)
};

int ServiceRouter::route(int routine, U64 p1, U64 p2, U64 /* rcx */, U64 p3, U64 p4) {
	if (routine < (int)SYSCALL_MIN || routine > (int)SYSCALL_MAX) {
		Message::brief << "Unknown system call: " << routine << "\n";
		for (;;)
			;
	}
	return (table[routine - SYSCALL_MIN])(p1, p2, p3, p4);
}

} // namespace kernel
