#ifndef KERNEL_SERVICE_SYSTEM_SERVICE_H_INCLUDED
#define KERNEL_SERVICE_SYSTEM_SERVICE_H_INCLUDED

#include "SystemService.h"
#include "Message.h"

namespace kernel {

int SystemService<SYSCALL_EXIT_PROCESS>::serve(int status) {
	Message::brief << status << " is the returned value\n";

	for (;;) ;
	return 0;
}

int SystemService<SYSCALL_RETURN_VALUE>::serve() {
	return 9006;
}

} // namespace kernel

#endif // KERNEL_SERVICE_SYSTEM_SERVICE_H_INCLUDED
