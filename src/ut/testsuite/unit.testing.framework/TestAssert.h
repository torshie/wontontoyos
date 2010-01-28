#ifndef KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_H_INCLUDED
#define KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_H_INCLUDED

#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestAssert : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testAssertTrue() {
		UT_ASSERT(true);
	}

	void testAssertFalse() {
		UT_ASSERT(false);
	}
};

} /* namespace kernel */

#endif
