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
	enum __ {
		HIGHEST_ADDRESS = 0xFFFFFFFFFFFFFFFF,
		LAST_POINTER = 0xFFFFFFFFFFFFFFF8
	};
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testMapAndUnmapTempPage() {
		Address physicalAddress = getSingleInstance<PhysicalPageAllocator>().allocate(PAGE_SIZE);
		void* virtualAddress = PageMap::mapTempPage(physicalAddress);
		UT_ASSERT_EQUAL(PageMap::unmapTempPage(virtualAddress), physicalAddress);
	}

	void testGetPointerToKernelAddressWithUnalignedAddress() {
		PagePointer<1>* aligned = PagePointer<1>::getPointerToKernelAddress(KERNEL_VIRTUAL_BASE);
		PagePointer<1>* unaligned = PagePointer<1>::getPointerToKernelAddress(
				KERNEL_VIRTUAL_BASE + 1);
		UT_ASSERT_EQUAL(aligned, unaligned);
	}

	void testGetPointerToKernelWithHighestAddress() {
		PagePointer<1>* one = PagePointer<1>::getPointerToKernelAddress(HIGHEST_ADDRESS);
		PagePointer<2>* two = PagePointer<2>::getPointerToKernelAddress(HIGHEST_ADDRESS);
		PagePointer<3>* three= PagePointer<3>::getPointerToKernelAddress(HIGHEST_ADDRESS);
		PagePointer<4>* four = PagePointer<4>::getPointerToKernelAddress(HIGHEST_ADDRESS);

		UT_ASSERT_EQUAL(one, LAST_POINTER);
		UT_ASSERT_EQUAL(two, LAST_POINTER);
		UT_ASSERT_EQUAL(three, LAST_POINTER);
		UT_ASSERT_EQUAL(four, LAST_POINTER);
	}

	void testGetPointerToKernelWithLastButOnePageAddress() {
		const static U64 ADDRESS = HIGHEST_ADDRESS - PAGE_SIZE;
		PagePointer<1>* one = PagePointer<1>::getPointerToKernelAddress(ADDRESS);
		PagePointer<2>* two = PagePointer<2>::getPointerToKernelAddress(ADDRESS);
		PagePointer<3>* three= PagePointer<3>::getPointerToKernelAddress(ADDRESS);
		PagePointer<4>* four = PagePointer<4>::getPointerToKernelAddress(ADDRESS);

		UT_ASSERT_EQUAL(four, LAST_POINTER);
		UT_ASSERT_EQUAL(three, LAST_POINTER);
		UT_ASSERT_EQUAL(two, LAST_POINTER);
		UT_ASSERT_EQUAL(one, LAST_POINTER - sizeof(PagePointer<1>));
	}
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_MAP_H_INCLUDED */
