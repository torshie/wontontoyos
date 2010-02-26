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
				+ PagePointer<4>::MEMORY_POINTED);
		PageTable<3>* table = PageTable<3>::create(KERNEL_VIRTUAL_BASE
				+ PagePointer<4>::MEMORY_POINTED);
		UT_ASSERT_EQUAL(table, pointer);
		UT_ASSERT_FALSE(table->pointer[0].present);
		UT_ASSERT_FALSE(table->pointer[1].present);
		UT_ASSERT_FALSE(table->pointer[PagePointer<3>::POINTERS_PER_PAGE - 1].present);

		PageTable<3>::destroy(table);
	}
};

} /* namespace kernel */

#endif /* KERNEL_MEMORY_MANAGEMENT_TEST_PAGE_TABLE_H_INCLUDED */
