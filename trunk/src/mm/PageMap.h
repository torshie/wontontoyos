#ifndef KERNEL_ARCH_PAGE_MAP_H_INCLUDED
#define KERNEL_ARCH_PAGE_MAP_H_INCLUDED

#include "PagePointer.h"
#include <generic/type.h>
#include <kernel/abi.h>
#include <cxx/BUG.h>

namespace kernel {

// XXX Implement destroy
class PageMap {
	~PageMap() {}

	template<int LEVEL> class PageMapHelper {
	public:
		static void create(Address base, Size size);
	};

public:
	static void* mapTempPage(Address physicalAddress);
	static Address unmapTempPage(void*);
	static void reload();
	static void create(Address base, Size size) {
		PageMapHelper<4>::create(base, size);
		PageMapHelper<3>::create(base, size);
		PageMapHelper<2>::create(base, size);
		PageMapHelper<1>::create(base, size);
	}
};

template<int LEVEL> void PageMap::PageMapHelper<LEVEL>::create(Address base,
		Size size) {
	Address start = Utils::roundDown(base, PagePointer<LEVEL>::MEMORY_POINTED);
	Address end = Utils::roundUp(base + size, PagePointer<LEVEL>::MEMORY_POINTED);
	for (Address address = start; address < end;
			address += PagePointer<LEVEL>::MEMORY_POINTED) {
		PagePointer<LEVEL>* pointer = PagePointer<LEVEL>::getPointerTo(address);
		if (!(pointer->present)) {
			PageTable<LEVEL - 1>::create(address);
		}
	}
}

} // namespace kernel

#endif // KERNEL_ARCH_PAGE_MAP_H_INCLUDED
