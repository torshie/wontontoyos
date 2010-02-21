#ifndef KERNEL_ARCH_PAGE_MAP_H_INCLUDED
#define KERNEL_ARCH_PAGE_MAP_H_INCLUDED

#include "PagePointer.h"
#include <generic/type.h>
#include <kernel/abi.h>
#include <cxx/BUG.h>

namespace kernel {

class PageMap {
public:
	static void* mapTempPage(Address physicalAddress);
	static Address unmapTempPage(void*);
	static void reload();
//
//	template<int LEVEL>
//	static PagePointer<LEVEL>* getPointerToKernelAddress(Address virtualAddress) {
//		if (virtualAddress < KERNEL_VIRTUAL_BASE) {
//			BUG("Invalid kernel address " << virtualAddress);
//		}
//
//		Address alignedAddress = virtualAddress / PagePointer<LEVEL>::SIZE_OF_POINTED_MEMORY
//				* PagePointer<LEVEL>::SIZE_OF_POINTED_MEMORY;
//
//		U64 numberOfPointers = (-alignedAddress) / PagePointer<LEVEL>::SIZE_OF_POINTED_MEMORY;
//		U64 spaceUsed = numberOfPointers * sizeof(PagePointer<LEVEL>);
//		return (PagePointer<LEVEL>*)(-spaceUsed);
//	}
};

} /* namespace kernel */

#endif /* KERNEL_ARCH_PAGE_MAP_H_INCLUDED */
