#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_TABLE_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_TABLE_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/PageTable.h"
#include <cxx/BUG.h>

namespace kernel {

class TestPageTable : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testCreateLevelThreePageTable() {
		PagePointer<3>* pointer = PagePointer<3>::getPointerToKernelAddress(KERNEL_VIRTUAL_BASE
				+ PagePointer<4>::SIZE_OF_POINTED_MEMORY);
		PageTable<3>* table = PageTable<3>::create(pointer);
		UT_ASSERT_TRUE(pointer->present);
		UT_ASSERT_TRUE(pointer->writable);
	}
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_TABLE_H_INCLUDED */
