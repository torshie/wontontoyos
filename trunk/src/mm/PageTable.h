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

		POINTERS_PER_TABLE = PAGE_SIZE / sizeof(PagePointer<LEVEL>),
	};

	PagePointer<LEVEL> pointer[POINTERS_PER_TABLE];

	static PageTable* create(unsigned long, Address virtualAddress);
	static void destroy(PageTable*);
};

namespace internal {

/**
 * Used to make sure the data structure is correctly packed.
 *
 * If the data structure isn't packed as expected, we will get compile
 * time error.
 */
typedef int StaticSizeChecker[sizeof(PageTable<4>) == PAGE_SIZE ? 1 : -1];
typedef int StaticSizeChecker[sizeof(PageTable<3>) == PAGE_SIZE ? 1 : -1];
typedef int StaticSizeChecker[sizeof(PageTable<2>) == PAGE_SIZE ? 1 : -1];
typedef int StaticSizeChecker[sizeof(PageTable<1>) == PAGE_SIZE ? 1 : -1];

} /* namespace internal */

template<int LEVEL>
PageTable<LEVEL>* PageTable<LEVEL>::create(unsigned long,
		Address virtualAddress) {
	if (virtualAddress < BASE_ADDRESS
			|| virtualAddress % PAGE_SIZE != 0) {
		return 0;
	}

	PhysicalPageAllocator& allocator = getSingleInstance<PhysicalPageAllocator>();

	Address physicalAddress = (Address)allocator.allocate(1);

	return (PageTable<LEVEL>*)virtualAddress;
}

} /* namespace kernel */

#endif
