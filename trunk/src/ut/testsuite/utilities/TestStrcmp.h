#include <generic/Utils.h>
#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestStrcmp : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testEqualString() {
		UT_ASSERT_EQUAL(Utils::strcmp("hello", "hello"), 0);
	}

	void testWhenLengthIsGiven() {
		UT_ASSERT_EQUAL(Utils::strcmp("abchello", "abc", 3), 0);
	}
};

} // namespace kernel
