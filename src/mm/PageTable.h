#ifndef KERNEL_ARCH_PAGE_TABLE_H_INCLUDED
#define KERNEL_ARCH_PAGE_TABLE_H_INCLUDED

#include "arch/X64Constant.h"
#include "PagePointer.h"
#include "mm/PhysicalPageAllocator.h"
#include <generic/getSingleInstance.h>
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
		BASE_ADDRESS =
				LEVEL == 4 ? 0xFFFFFFFFFFFFF000 :
				LEVEL == 3 ? 0xFFFFFFFFFFE00000 :
				LEVEL == 2 ? 0xFFFFFFFFC0000000 :
				LEVEL == 1 ? 0xFFFFFF8000000000 : 0,
	};

	PagePointer<LEVEL> pointer[PagePointer<LEVEL>::NUMBER_OF_POINTERS_PER_PAGE];

	static PageTable* create(unsigned long, Address virtualAddress);
	static void destroy(PageTable*);
};

STATIC_ASSERT_EQUAL(sizeof(PageTable<1>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<2>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<3>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<4>), PAGE_SIZE)

/**
 * XXX Test this method
 */
template<int LEVEL>
PageTable<LEVEL>* PageTable<LEVEL>::create(unsigned long, Address virtualAddress) {
	if (virtualAddress < BASE_ADDRESS || virtualAddress % PAGE_SIZE != 0) {
		return 0;
	}

	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();

	Address physicalAddress = (Address)allocator.allocate(1);
	PageTable<LEVEL>* pageTable = (PageTable<LEVEL>*)PageMap::mapTempPage(physicalAddress);
	new (pageTable)PageTable<LEVEL>();

	return (PageTable<LEVEL>*)virtualAddress;
}

} /* namespace kernel */

#endif
