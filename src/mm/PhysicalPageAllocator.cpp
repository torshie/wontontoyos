#include "PhysicalPageAllocator.h"
#include "System.h"
#include "arch/X64Constant.h"

namespace kernel {

/**
 * Defined in linker script
 */
extern "C" char __ld_bss_end;
PhysicalPageAllocator::PhysicalPageAllocator() {
	numberOfAllocatedPages = (Address)&__ld_bss_end / PAGE_SIZE;
}

/**
 * XXX Implement this method
 * XXX Make this method thread-safe
 */
void* PhysicalPageAllocator::allocate(Size numberOfNeededPages) {
	void* result = (void*)(numberOfAllocatedPages * PAGE_SIZE);
	numberOfAllocatedPages += numberOfNeededPages;
	return result;
}

/**
 * XXX Implement this method
 */
void PhysicalPageAllocator::release(void*) {
}

} /* namespace kernel */
