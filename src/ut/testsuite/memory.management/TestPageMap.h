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

	void testCreateKernelMap_MappedAddress() {
		volatile bool b = true;
		PageMap::createKernelMap((Address)&b, PAGE_SIZE);
		UT_ASSERT_TRUE(b);
	}

	void testCreateKernelMap_NewAddress() {
		Address address = KERNEL_VIRTUAL_BASE + PagePointer<4>::MEMORY_POINTED + PAGE_SIZE;
		Size size = PagePointer<2>::MEMORY_POINTED;
		PageMap::createKernelMap(address, size);
		volatile int* first = (volatile int*)address;
		volatile int* second = (volatile int*)(address + sizeof(int));
		*first = 4321;
		*second = 4321;
		UT_ASSERT_EQUAL(*first, *second);
		// XXX Destroy the created map hierarchy
	}

	void testCreateUserMap_NewAddress() {
		Address base = PagePointer<4>::MEMORY_POINTED + PAGE_SIZE;
		Size size = PagePointer<2>::MEMORY_POINTED;
		PageMap::createKernelMap(base, size);
		volatile int* first = (volatile int*)base;
		volatile int* second = (volatile int*)(base + sizeof(int));
		*first = 1234;
		*second = 1234;
		UT_ASSERT_EQUAL(*first, *second);
		// XXX Destroy the created map hierarchy
	}
};

} /* namespace kernel */
