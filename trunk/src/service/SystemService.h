#ifndef KERNEL_SYSTEM_SERVICE_H_INCLUDED
#define KERNEL_SYSTEM_SERVICE_H_INCLUDED

#include <kernel/abi.h>

namespace kernel {

template<int SERVICE> class SystemService;

template<> class SystemService<SYSCALL_EXIT_PROCESS> {
public:
	static int serve(int status);
};

template<> class SystemService<SYSCALL_RETURN_VALUE> {
public:
	static int serve();
};

} // namespace kernel

#endif // KERNEL_SYSTEM_SERVICE_H_INCLUDED
