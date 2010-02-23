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

	void testMapAndUnmapTempPage() {
		Address physicalAddress = getSingleInstance<PhysicalPageAllocator>().allocate(PAGE_SIZE);
		void* virtualAddress = PageMap::mapTempPage(physicalAddress);
		UT_ASSERT_EQUAL(PageMap::unmapTempPage(virtualAddress), physicalAddress);
	}
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED */
