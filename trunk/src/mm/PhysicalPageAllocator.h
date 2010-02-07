#ifndef KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class PhysicalPageAllocator {
public:
	PhysicalPageAllocator();

	Address allocate(Size numberOfNeededPages);
	void release(Address);

private:
	Size numberOfAllocatedPages;
};

} /* namespace kernel */

#endif /* KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED */
