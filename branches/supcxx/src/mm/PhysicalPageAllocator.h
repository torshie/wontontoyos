#ifndef KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>

namespace kernel {

class PhysicalPageAllocator {
	friend PhysicalPageAllocator& getSingleInstance<PhysicalPageAllocator>();
	PhysicalPageAllocator(const PhysicalPageAllocator&);
	const PhysicalPageAllocator& operator = (const PhysicalPageAllocator&);

	PhysicalPageAllocator();

public:
	Address allocate(Size memoryNeeded);
	void release(Address);

private:
	Size available;
};

} // namespace kernel

#endif // KERNEL_MM_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED
