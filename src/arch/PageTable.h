#ifndef KERNEL_ARCH_PAGE_TABLE_H_INCLUDED
#define KERNEL_ARCH_PAGE_TABLE_H_INCLUDED

#include "X64Constant.h"
#include "PagePointer.h"
#include "mm/PhysicalPageAllocator.h"
#include <generic/type.h>

namespace kernel {

template<int LEVEL>
class PageTable {
private:
	PageTable() {}
	PageTable(const PageTable&);
	const PageTable& operator = (const PageTable&);

public:
	enum {
		BASE_VIRTUAL_ADDRESS =
				LEVEL == 4 ? 0xFFFFFFFFFFFFF000 :
				LEVEL == 3 ? 0xFFFFFFFFFFE00000 :
				LEVEL == 2 ? 0xFFFFFFFFC0000000 :
				LEVEL == 1 ? 0xFFFFFF8000000000 : 0
	};

	PagePointer<LEVEL> pointer[PAGE_SIZE / sizeof(PagePointer<LEVEL>)];

	static PageTable* create(unsigned long, Address virtualAddress);
	static void destroy(PageTable*);
};

template<int LEVEL>
PageTable<LEVEL>* PageTable<LEVEL>::create(unsigned long,
		Address virtualAddress) {
	if (virtualAddress < BASE_VIRTUAL_ADDRESS
			|| virtualAddress / PAGE_SIZE != 0) {
		return 0;
	}

	PhysicalPageAllocator&
	allocator = getSingleInstance<PhysicalPageAllocator>();

	Address physicalAddress = (Address)allocator.allocate(1);

	return (PageTable<LEVEL>*)virtualAddress;
}

} /* namespace kernel */

#endif
