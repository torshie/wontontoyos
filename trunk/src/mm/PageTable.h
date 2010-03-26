#ifndef KERNEL_ARCH_PAGE_TABLE_H_INCLUDED
#define KERNEL_ARCH_PAGE_TABLE_H_INCLUDED

#include "arch/X64Constant.h"
#include "PagePointer.h"
#include "PhysicalPageAllocator.h"
#include "PageMap.h"
#include <generic/getSingleInstance.h>
#include <generic/type.h>
#include <cxx/new.h>

namespace kernel {

// XXX Tune call of reload()
template<int LEVEL> class PageTable {
	friend class TestPageTable;
	friend class PageMap;

	PageTable() {}
	PageTable(const PageTable&);
	const PageTable& operator = (const PageTable&);

	static PageTable* create(Address virtualAddress);

	static void destroy(Address table);

public:
	enum __ {
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

// XXX Check canonical form
// XXX Check when should the userSpace bit be set.
template<int LEVEL> PageTable<LEVEL>* PageTable<LEVEL>::create(Address linearAddress) {
	Address pagePointerAddress =
			(Address)PagePointer<LEVEL>::getPointerTo(linearAddress);
	bool userSpace;
	if (linearAddress < KERNEL_VIRTUAL_BASE) {
		userSpace = true;
	} else {
		userSpace = false;
	}

	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();
	Address physicalAddress = (Address)allocator.allocate(PAGE_SIZE);
	PagePointer<1>* tmp = PagePointer<1>::getPointerTo(pagePointerAddress);
	tmp->page = physicalAddress / PAGE_SIZE;
	tmp->present = 1;
	tmp->writable = 1;
	tmp->cacheDisable = 1;
	if (userSpace) {
		tmp->userSpace = 1;
	}
	PageMap::reload();
	new ((void*)pagePointerAddress)PageTable();
	PageMap::reload();

	return (PageTable*)pagePointerAddress;
}

template<int LEVEL> void PageTable<LEVEL>::destroy(Address table) {
	for (Size i = 0; i < PagePointer<LEVEL>::POINTERS_PER_PAGE; ++i) {
		if (((PageTable*)(table))->pointer[i].present) {
			return;
		}
	}

	PagePointer<1>* tmp = PagePointer<1>::getPointerTo(table);
	Address physicalAddress = tmp->page * PAGE_SIZE;
	tmp->present = 0;
	PageMap::reload();
	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();
	allocator.release(physicalAddress);
}

} // namespace kernel

#endif // KERNEL_ARCH_PAGE_TABLE_H_INCLUDED
