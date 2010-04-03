#include "ut/framework/UnitTesting.h"
#include "Printer.h"

namespace kernel {

class TestMethodCall : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testMethodCall() {
		UT_ASSERT_TRUE(true);
	}
};

} /* namespace kernel */
