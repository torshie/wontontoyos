#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/PageMap.h"
#include "mm/PhysicalPageAllocator.h"
#include "Printer.h"

namespace kernel {

class TestPageMap : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testMapUnmapTempPage() {
//		Address physicalAddress = getSingleInstance<PhysicalPageAllocator>().allocate(1);
//		void* virtualAddress = PageMap::mapTempPage(physicalAddress);
//		Printer& console = getSingleInstance<Printer>();
//		console << virtualAddress << "\n";
//		UT_ASSERT_EQUAL(PageMap::unmapTempPage(virtualAddress), physicalAddress);
	}

private:
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED */
