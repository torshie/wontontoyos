#include "PageMap.h"
#include "PageTable.h"
#include "arch/X64Constant.h"
#include <kernel/abi.h>
#include "debug.h"

namespace kernel {

void* PageMap::mapTempPage(Address physicalAddress) {
	if (physicalAddress % PAGE_SIZE != 0) {
		BUG("Invalid physicalAddress: " << physicalAddress);
	}

	PagePointer<1>* freeVirtualPage = PagePointer<1>::getPointerToKernelAddress(
															KERNEL_TEMP_AREA_BEGIN);
	Offset offset = KERNEL_TEMP_AREA_BEGIN;
	for (; offset < KERNEL_TEMP_AREA_END; offset += PAGE_SIZE, ++freeVirtualPage) {
		if (!freeVirtualPage->present) {
			break;
		}
	}
	if (offset == KERNEL_TEMP_AREA_END) {
		return 0;
	}
	freeVirtualPage->physicalAddress = physicalAddress;
	freeVirtualPage->present = 1;
	freeVirtualPage->writable = 1;

	reload();

	return (void*)(offset);
}

Address PageMap::unmapTempPage(void* pointer) {
	if ((Address)pointer % PAGE_SIZE != 0) {
		BUG("Invalid virtual address: " << pointer);
	}

	PagePointer<1>* pagePointer = PagePointer<1>::getPointerToKernelAddress((Address)pointer);
	pagePointer->present = 0;

	reload();

	return pagePointer->page * PAGE_SIZE;
}

void PageMap::reload() {
	PageTable<4>* levelFour = (PageTable<4>*)(PageTable<4>::LOWEST_TABLE_ADDRESS);
	Address address = levelFour->pointer[PagePointer<4>::NUMBER_OF_POINTERS_PER_PAGE - 1].page
								* PAGE_SIZE;
	asm volatile("mov %0, %%cr3" : : "r"(address));
}

}


 /* namespace kernel */
