#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/PageMap.h"
#include "mm/PhysicalPageAllocator.h"
#include "Printer.h"
#include "mm/PageTable.h"
#include <kernel/abi.h>
#include "debug.h"

namespace kernel {

class TestPageMap : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testMapUnmapTempPage() {
		Address physicalAddress = getSingleInstance<PhysicalPageAllocator>().allocate(1);
		void* virtualAddress = PageMap::mapTempPage(physicalAddress);
		UT_ASSERT_EQUAL(PageMap::unmapTempPage(virtualAddress), physicalAddress);
	}

	void testGetPointerToKernelAddress_UnalignedAddress() {
		PagePointer<1>* aligned = PageMap::getPointerToKernelAddress<1>(KERNEL_VIRTUAL_BASE);
		PagePointer<1>* unaligned = PageMap::getPointerToKernelAddress<1>(
				KERNEL_VIRTUAL_BASE + 1);
		UT_ASSERT_EQUAL(aligned, unaligned);
	}

	void testGetPointerToKernelAddressWithSelfReferencEntry() {
		PagePointer<4>* pointer = PageMap::getPointerToKernelAddress<4>(PageTable<1>::BASE_ADDRESS);
		UT_ASSERT_EQUAL(pointer, (-sizeof(PagePointer<4>)));
	}
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED */
