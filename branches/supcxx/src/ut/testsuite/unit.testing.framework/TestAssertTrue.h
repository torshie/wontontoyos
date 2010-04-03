#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestAssertTrue : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testTrue() {
		UT_ASSERT_TRUE(true);
	}

	void testFalse() {
//		UT_ASSERT_TRUE(false);
	}
};

} /* namespace kernel */
