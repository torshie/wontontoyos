#ifndef KERNEL_ARCH_PAGE_TABLE_H_INCLUDED
#define KERNEL_ARCH_PAGE_TABLE_H_INCLUDED

#include "arch/X64Constant.h"
#include "PagePointer.h"
#include "mm/PhysicalPageAllocator.h"
#include "PageMap.h"
#include <generic/getSingleInstance.h>
#include <generic/type.h>
#include <cxx/new.h>

namespace kernel {

template<int LEVEL>
class PageTable {
private:
	PageTable() {}
	PageTable(const PageTable&);
	const PageTable& operator = (const PageTable&);

public:
	enum {
		LOWEST_TABLE_ADDRESS =
				LEVEL == 4 ? 0xFFFFFFFFFFFFF000 :
				LEVEL == 3 ? 0xFFFFFFFFFFE00000 :
				LEVEL == 2 ? 0xFFFFFFFFC0000000 :
				LEVEL == 1 ? 0xFFFFFF8000000000 : 0,
	};

	PagePointer<LEVEL> pointer[PagePointer<LEVEL>::POINTERS_PER_PAGE];

	static PageTable* create(Address virtualAddress);
	static void destroy(PageTable* table);

	static PageTable* create(void* pointer) {
		return create((Address)pointer);
	}

};

STATIC_ASSERT_EQUAL(sizeof(PageTable<1>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<2>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<3>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<4>), PAGE_SIZE)

template<int LEVEL>
PageTable<LEVEL>* PageTable<LEVEL>::create(Address virtualAddress) {
	if ((virtualAddress < LOWEST_TABLE_ADDRESS && virtualAddress != 0)
			|| virtualAddress % PAGE_SIZE != 0) {
		BUG("Invalid virtual address: " << virtualAddress);
	}

	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();

	Address physicalAddress = (Address)allocator.allocate(PAGE_SIZE);
	PageTable<LEVEL>* pageTable = (PageTable<LEVEL>*)PageMap::mapTempPage(physicalAddress);
	new (pageTable)PageTable<LEVEL>();
	PageMap::unmapTempPage(pageTable);

	if (virtualAddress != 0) {
		PagePointer<1>* pointer = PagePointer<1>::getPointerToKernelAddress(virtualAddress);
		pointer->page = physicalAddress / PAGE_SIZE;
		pointer->present = 1;
		pointer->writable = 1;
		PageMap::reload();
	}

	return (PageTable<LEVEL>*)virtualAddress;
}

template<int LEVEL>
void PageTable<LEVEL>::destroy(PageTable* table) {
	PagePointer<1>* pointer = PagePointer<1>::getPointerToKernelAddress(table);
	Address physicalAddress = pointer->page * PAGE_SIZE;
	pointer->present = 0;
	PageMap::reload();
	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();
	allocator.release(physicalAddress);
}

} /* namespace kernel */

#endif
