#include "X64Core.h"

namespace kernel {

U64 X64Core::readModelSpecificAddress(U32 msr) {
	U32 lowerHalf;
	U32 higherHalf;
	asm volatile ("mov %2, %%ecx\n"
			"rdmsr\n"
			"mov %%edx, %0\n"
			"mov %%eax, %1\n"
			: "=m"(higherHalf), "=m"(lowerHalf)
			: "r"(msr));
	return (U64)lowerHalf | (((U64)higherHalf) << 32);
}

} /* namespace kernel */
