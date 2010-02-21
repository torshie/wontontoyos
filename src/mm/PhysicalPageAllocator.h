#ifndef KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class PhysicalPageAllocator {
public:
	PhysicalPageAllocator();

	Address allocate(Size memoryNeeded);
	void release(Address);

private:
	Size available;
};

} /* namespace kernel */

#endif /* KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED */
