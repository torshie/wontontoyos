#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestOperatorNew : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testNew() {
		int* value = new int(0x900D);
		UT_ASSERT_EQUAL(*value, 0x900D);
	}
};

} // namespace kernel
