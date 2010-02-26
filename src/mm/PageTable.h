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

template<int LEVEL> class PageTable {
	friend class TestPageTable;
	friend class PageMap;

	PageTable() {}
	PageTable(const PageTable&);
	const PageTable& operator = (const PageTable&);

	static PageTable* create(Address virtualAddress);
	static PageTable* create(void* pointer) {
		return create((Address)pointer);
	}

	static void destroy(PageTable* table);

public:
	enum {
		LOWEST_TABLE_ADDRESS =
				LEVEL == 4 ? 0xFFFFFFFFFFFFF000 :
				LEVEL == 3 ? 0xFFFFFFFFFFE00000 :
				LEVEL == 2 ? 0xFFFFFFFFC0000000 :
				LEVEL == 1 ? 0xFFFFFF8000000000 : 0,
	};

	PagePointer<LEVEL> pointer[PagePointer<LEVEL>::POINTERS_PER_PAGE];
};

STATIC_ASSERT_EQUAL(sizeof(PageTable<1>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<2>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<3>), PAGE_SIZE)
STATIC_ASSERT_EQUAL(sizeof(PageTable<4>), PAGE_SIZE)

template<int LEVEL> PageTable<LEVEL>* PageTable<LEVEL>::create(Address kernelAddress) {
	if (kernelAddress < KERNEL_VIRTUAL_BASE) {
		BUG("Address " << kernelAddress << " isn't a kernel space address");
	}

	Address tableAddress = (Address)PagePointer<LEVEL>::getPointerToKernelAddress(kernelAddress);
	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();
	Address physicalAddress = (Address)allocator.allocate(PAGE_SIZE);
	PageTable<LEVEL>* pageTable = (PageTable<LEVEL>*)PageMap::mapTempPage(physicalAddress);
	new (pageTable)PageTable<LEVEL>();
	PageMap::unmapTempPage(pageTable);

	PagePointer<1>* pointer = PagePointer<1>::getPointerToKernelAddress(tableAddress);
	pointer->page = physicalAddress / PAGE_SIZE;
	pointer->present = 1;
	pointer->writable = 1;
	PageMap::reload();

	return (PageTable<LEVEL>*)tableAddress;
}

template<int LEVEL> void PageTable<LEVEL>::destroy(PageTable* table) {
	PagePointer<1>* pointer = PagePointer<1>::getPointerToKernelAddress(table);
	Address physicalAddress = pointer->page * PAGE_SIZE;
	pointer->present = 0;
	PageMap::reload();
	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();
	allocator.release(physicalAddress);
}

} /* namespace kernel */

#endif
