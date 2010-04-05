#include "PageMap.h"
#include "PageTable.h"
#include "arch/X64Constant.h"
#include <kernel/abi.h>
#include "debug.h"
#include "arch/Processor.h"
#include <generic/Utils.h>

namespace kernel {

void PageMap::reload() {
	PageTable<4>* levelFour = (PageTable<4>*)(PageTable<4>::LOWEST_TABLE_ADDRESS);
	Address address = levelFour->pointer[PagePointer<4>::POINTERS_PER_PAGE - 1].page
								* PAGE_SIZE;
	Processor::Register<Processor::CR3>::set(address);
}

void PageMap::create(Address linear, Size size, Address physical, bool replace) {
	// XXX Mark the given physical address in PhysicalPageAllocator if necessary
	// XXX Mark the given linear address in GenericAllocator if necessary
	if (physical % PAGE_SIZE != 0) {
		BUG("Bad physical address: " << physical);
	}
	PageMapHelper<4>::create(linear, size);
	PageMapHelper<3>::create(linear, size);
	PageMapHelper<2>::create(linear, size);
	Address start = Utils::roundDown(linear, PAGE_SIZE);
	Address end = Utils::roundUp(linear + size, PAGE_SIZE);
	bool userSpace;
	if (linear < KERNEL_VIRTUAL_BASE) {
		userSpace = true;
	} else {
		userSpace = false;
	}
	for (Address linearAddress = start, physicalAddress = physical;
			linearAddress < end;
			physicalAddress += PAGE_SIZE, linearAddress += PAGE_SIZE) {
		// XXX Do something if the an old page already exists
		PagePointer<1>* pointer = PagePointer<1>::getPointerTo(linearAddress);
		if (!pointer->present) {
			pointer->address = physicalAddress;
			pointer->present = 1;
			pointer->writable = 1;
			if (userSpace) {
				pointer->userSpace = 1;
			}
		} else {
			if (replace) {
				pointer->page = physical / PAGE_SIZE;
			}
		}
	}
	PageMap::reload();
}

} // namespace kernel
