#include "ut/framework/UnitTesting.h"
#include "Printer.h"

namespace kernel {

class TestSetUpAndTearDown : public TestCase {
	int counter;
public:
	TestSetUpAndTearDown() : counter(0) {}

	bool getTestPoint(TestPoint& point, const char*& name);

	void setUp() {
		UT_ASSERT_EQUAL(counter, 0);
	}

	void tearDown() {
		UT_ASSERT_EQUAL(counter, 1);
	}

	void testDummy() {
		counter++;
	}
};

} /* namespace kernel */
