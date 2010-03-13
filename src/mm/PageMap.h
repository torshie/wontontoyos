#ifndef KERNEL_ARCH_PAGE_MAP_H_INCLUDED
#define KERNEL_ARCH_PAGE_MAP_H_INCLUDED

#include "PagePointer.h"
#include <generic/type.h>
#include <kernel/abi.h>
#include <cxx/BUG.h>

namespace kernel {

class PageMap {
	~PageMap() {}

	template<int LEVEL> class CreateKernelHierarchyHelper {
	public:
		static void run(Address base, Size size);
	};

public:
	static void* mapTempPage(Address physicalAddress);
	static Address unmapTempPage(void*);
	static void reload();
	static void createKernelHierarchy(Address base, Size size) {
		CreateKernelHierarchyHelper<1>::run(base, size);
	}
	static void createKernelHierarchy(void* base, Size size) {
		createKernelHierarchy((Address)base, size);
	}
};

template<int LEVEL> void PageMap::CreateKernelHierarchyHelper<LEVEL>::run(Address base,
		Size size) {
	CreateKernelHierarchyHelper<LEVEL + 1>::run(base, size);

	Address start = Utils::roundDown(base, PagePointer<LEVEL>::MEMORY_POINTED);
	Address end = Utils::roundUp(base + size, PagePointer<LEVEL>::MEMORY_POINTED);
	for (Address address = start; address < end;
			address += PagePointer<LEVEL>::MEMORY_POINTED) {
		PagePointer<LEVEL>* pointer = PagePointer<LEVEL>::getPointerToKernelAddress(address);
		if (pointer->present) {
			continue;
		}
		PageTable<LEVEL - 1>::create(address);
	}
}

template<> inline void PageMap::CreateKernelHierarchyHelper<5>::run(Address, Size) {}

} /* namespace kernel */

#endif /* KERNEL_ARCH_PAGE_MAP_H_INCLUDED */
