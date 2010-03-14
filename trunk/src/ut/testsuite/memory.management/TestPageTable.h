#include "ut/framework/UnitTesting.h"
#include "mm/PageTable.h"
#include <cxx/BUG.h>

namespace kernel {

class TestPageTable : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testCreateLevelThreePageTable() {
		PageTable<3>* table = PageTable<3>::create(KERNEL_VIRTUAL_BASE
				+ PagePointer<4>::MEMORY_POINTED);
		UT_ASSERT_FALSE(table->pointer[0].present);
		UT_ASSERT_FALSE(table->pointer[1].present);
		UT_ASSERT_FALSE(table->pointer[PagePointer<3>::POINTERS_PER_PAGE - 1].present);

		PageTable<3>::destroy(table);
	}
};

} /* namespace kernel */
