#include "PhysicalPageAllocator.h"
#include "arch/X64Constant.h"
#include <cxx/BUG.h>
#include <kernel/abi.h>

namespace kernel {

// Defined in ld script
extern "C" char __ld_image_end, __ld_image_start;
PhysicalPageAllocator::PhysicalPageAllocator() {
	Size imageSize = (Address)&__ld_image_end - (Address)&__ld_image_start;
	available = imageSize + KERNEL_RESERVED_MEMORY + APIC_MEMORY_SIZE + KERNEL_STACK_SIZE;
}

// XXX Implement this method
// XXX Make this method thread-safe
Address PhysicalPageAllocator::allocate(Size memoryNeeded) {
	if (memoryNeeded % PAGE_SIZE != 0) {
		BUG("Cannot allocate " << memoryNeeded << " bytes");
	}

	Address result = available;
	available += memoryNeeded;
	return result;
}

// XXX Implement this method
void PhysicalPageAllocator::release(Address) {
}

} // namespace kernel
