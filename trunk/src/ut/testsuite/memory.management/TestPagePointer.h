#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_POINTER_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_POINTER_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/PagePointer.h"

namespace kernel {

class TestPagePointer : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testNumberOfPointersPerPage() {
		UT_ASSERT_EQUAL((I64)PagePointer<1>::NUMBER_OF_POINTERS_PER_PAGE, 512);
		UT_ASSERT_EQUAL((I64)PagePointer<2>::NUMBER_OF_POINTERS_PER_PAGE, 512);
		UT_ASSERT_EQUAL((I64)PagePointer<3>::NUMBER_OF_POINTERS_PER_PAGE, 512);
		UT_ASSERT_EQUAL((I64)PagePointer<4>::NUMBER_OF_POINTERS_PER_PAGE, 512);
	}

	void testSizeOfPointedMemory() {
		UT_ASSERT_EQUAL((I64)PagePointer<1>::SIZE_OF_POINTED_MEMORY, 4096);
		UT_ASSERT_EQUAL((I64)PagePointer<2>::SIZE_OF_POINTED_MEMORY, 4096 * 512);
		UT_ASSERT_EQUAL((I64)PagePointer<3>::SIZE_OF_POINTED_MEMORY, 4096 * 512 * 512);
		UT_ASSERT_EQUAL((I64)PagePointer<4>::SIZE_OF_POINTED_MEMORY, 4096LL * 512 * 512 * 512);
	}
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_POINTER_H_INCLUDED */
