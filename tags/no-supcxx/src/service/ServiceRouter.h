#ifndef KERNEL_ARCH_SERVICE_ROUTER_H_INCLUDED
#define KERNEL_ARCH_SERVICE_ROUTER_H_INCLUDED

#include <generic/type.h>
#include <kernel/abi.h>

namespace kernel {

class ServiceRouter {
public:
	static int route(int routine, U64 p1, U64 p2, U64 /* rcx */, U64 p3, U64 p4);

private:
	typedef int (*Service)(U64, U64, U64, U64);

	static Service table[SYSCALL_COUNT];
};

} // namespace kernel

#endif // KERNEL_ARCH_SERVICE_ROUTER_H_INCLUDED
