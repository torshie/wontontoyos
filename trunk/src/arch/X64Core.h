#ifndef KERNEL_ARCH_X64_CORE_H_INCLUDED
#define KERNEL_ARCH_X64_CORE_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class X64Core {
public:
	U64 readModelSpecificAddress(U32 msr);
};

} /* namespace kernel */

#endif /* KERNEL_ARCH_X64_CORE_H_INCLUDED */
