#include "ut/framework/UnitTesting.h"
#include <sexy/IS_CLASS.h>

namespace kernel {

class TestIS_CLASS : public TestCase {
	enum Enum {};
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testClass() {
		UT_ASSERT_TRUE(IS_CLASS<TestCase>::value);
	}

	void testInteger() {
		UT_ASSERT_FALSE(IS_CLASS<int>::value);
	}

	void testVoid() {
		UT_ASSERT_FALSE(IS_CLASS<void>::value);
	}

	void testEnum() {
		UT_ASSERT_FALSE(IS_CLASS<Enum>::value);
	}
};

} /* namespace kernel */
