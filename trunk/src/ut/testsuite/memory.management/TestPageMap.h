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

	void testCreateKernelHierarchyMappedAddress() {
		volatile bool b = true;
		PageMap::createKernelHierarchy((Address)&b, PAGE_SIZE);
		UT_ASSERT_TRUE(b);
	}

	void testCreateKernelHierarchy() {
		Address address = KERNEL_VIRTUAL_BASE + PagePointer<4>::MEMORY_POINTED + PAGE_SIZE;
		PageMap::createKernelHierarchy(address, PagePointer<2>::MEMORY_POINTED);
		volatile int* first = (volatile int*)address;
		volatile int* second = (volatile int*)(address + sizeof(int));
		*first = 4321;
		*second = 4321;
		UT_ASSERT_EQUAL(*first, *second);
		// XXX Destroy the created map hierarchy.
	}
};

} /* namespace kernel */
