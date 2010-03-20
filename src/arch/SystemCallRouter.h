#ifndef KERNEL_ARCH_SYSTEM_CALL_ROUTER_H_INCLUDED
#define KERNEL_ARCH_SYSTEM_CALL_ROUTER_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class SystemCallRouter {
public:
	/**
	 * Pass parameter with register %rdi, %rdx, %r8, %r9
	 */
	static void route(int routine, U64 p1, Address returnAddress, U64 p2, U64 p3, U64 p4);
};

} // namespace kernel

#endif // KERNEL_ARCH_SYSTEM_CALL_ROUTER_H_INCLUDED
