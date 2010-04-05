#include "Processor.h"
#include "X64Constant.h"
#include "GlobalDescriptorTable.h"
#include "Message.h"

namespace kernel {

#ifndef __X86_32__
extern "C" void (*bootServiceRouter)();
void Processor::initializeUserMode() {
	U64 star = (((U64)(GlobalDescriptorTable::OFFSET_USER_DATA - 8) | 3) << 48)
			| ((U64)GlobalDescriptorTable::OFFSET_KERNEL_CODE << 32);
	setModeSpecificRegister(MSR_SYS_TARGET_ADDRESS_REGISTER, star);
	setModeSpecificRegister(MSR_SYSCALL_FLAG_MASK, 0xFFFFFFFF);
	setModeSpecificRegister(MSR_LONG_SYSCALL_TARGET_ADDRESS_REGISTER, (U64)(&bootServiceRouter));
}
#endif

U64 Processor::getModelSpecificRegister(U32 reg) {
	U32 low;
	U32 high;
	asm volatile("rdmsr" : "=d"(high), "=a"(low) : "c"(reg));
	return (((U64)high) << 32) | low;
}

void Processor::setModeSpecificRegister(U32 reg, U64 value) {
	U32 low = (U32)value;
	U32 high = value >> 32;
	asm volatile("wrmsr" : : "c"(reg), "d"(high), "a"(low));
}

void Processor::halt() {
	for (;;) {
		asm volatile("hlt");
	}
}

} // namespace kernel
