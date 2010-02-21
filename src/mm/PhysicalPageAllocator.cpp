#include "PhysicalPageAllocator.h"
#include "System.h"
#include "arch/X64Constant.h"
#include <cxx/BUG.h>
#include <kernel/abi.h>

namespace kernel {

/**
 * Defined in linker script
 */
extern "C" char __ld_bss_end, __ld_image_start;
PhysicalPageAllocator::PhysicalPageAllocator() {
	Size imageSize = (Address)&__ld_bss_end - (Address)&__ld_image_start;
	available = imageSize + KERNEL_RESERVED_MEMORY + KERNEL_TEMP_AREA + KERNEL_STACK_SIZE;
}

/**
 * XXX Implement this method
 * XXX Make this method thread-safe
 */
Address PhysicalPageAllocator::allocate(Size memoryNeeded) {
	if (memoryNeeded % PAGE_SIZE != 0) {
		BUG("Cannot allocate " << memoryNeeded << " bytes");
	}

	Address result = available;
	available += memoryNeeded;
	return result;
}

/**
 * XXX Implement this method
 */
void PhysicalPageAllocator::release(Address) {
}

} /* namespace kernel */
