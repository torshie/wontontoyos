#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_POINTER_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_POINTER_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/PagePointer.h"
#include "mm/PageTable.h"

namespace kernel {

class TestPagePointer : public TestCase {
	enum __ {
		HIGHEST_ADDRESS = 0xFFFFFFFFFFFFFFFF,
		LAST_POINTER = 0xFFFFFFFFFFFFFFF8
	};
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testGetPointerToKernelAddressUnalignedAddress() {
		PagePointer<1>* aligned = PagePointer<1>::getPointerToKernelAddress(KERNEL_VIRTUAL_BASE);
		PagePointer<1>* unaligned = PagePointer<1>::getPointerToKernelAddress(
				KERNEL_VIRTUAL_BASE + 1);
		UT_ASSERT_EQUAL(aligned, unaligned);
	}

	void testGetPointerToKernelAddressHighestAddress() {
		PagePointer<1>* one = PagePointer<1>::getPointerToKernelAddress(HIGHEST_ADDRESS);
		PagePointer<2>* two = PagePointer<2>::getPointerToKernelAddress(HIGHEST_ADDRESS);
		PagePointer<3>* three= PagePointer<3>::getPointerToKernelAddress(HIGHEST_ADDRESS);
		PagePointer<4>* four = PagePointer<4>::getPointerToKernelAddress(HIGHEST_ADDRESS);

		UT_ASSERT_EQUAL(one, LAST_POINTER);
		UT_ASSERT_EQUAL(two, LAST_POINTER);
		UT_ASSERT_EQUAL(three, LAST_POINTER);
		UT_ASSERT_EQUAL(four, LAST_POINTER);
	}

	void testGetPointerToKernelAddressLastButOnePageAddress() {
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

	void testGetPointerToUserAddressZero() {
		PagePointer<1>* one = PagePointer<1>::getPointerToUserAddress((Address)0);
		PagePointer<2>* two = PagePointer<2>::getPointerToUserAddress((Address)0);
		PagePointer<3>* three = PagePointer<3>::getPointerToUserAddress((Address)0);
		PagePointer<4>* four = PagePointer<4>::getPointerToUserAddress((Address)0);

		UT_ASSERT_EQUAL(one, PageTable<1>::LOWEST_TABLE_ADDRESS);
		UT_ASSERT_EQUAL(two, PageTable<2>::LOWEST_TABLE_ADDRESS);
		UT_ASSERT_EQUAL(three, PageTable<3>::LOWEST_TABLE_ADDRESS);
		UT_ASSERT_EQUAL(four, PageTable<4>::LOWEST_TABLE_ADDRESS);
	}

	void testGetPointerToUserAddressSecondPageAddress() {
		PagePointer<1>* one = PagePointer<1>::getPointerToUserAddress((Address)PAGE_SIZE);
		PagePointer<2>* two = PagePointer<2>::getPointerToUserAddress((Address)PAGE_SIZE);
		PagePointer<3>* three = PagePointer<3>::getPointerToUserAddress((Address)PAGE_SIZE);
		PagePointer<4>* four = PagePointer<4>::getPointerToUserAddress((Address)PAGE_SIZE);

		UT_ASSERT_EQUAL(one, PageTable<1>::LOWEST_TABLE_ADDRESS + sizeof(PagePointer<1>));
		UT_ASSERT_EQUAL(two, PageTable<2>::LOWEST_TABLE_ADDRESS);
		UT_ASSERT_EQUAL(three, PageTable<3>::LOWEST_TABLE_ADDRESS);
		UT_ASSERT_EQUAL(four, PageTable<4>::LOWEST_TABLE_ADDRESS);
	}
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_POINTER_H_INCLUDED */
