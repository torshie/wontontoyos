#ifndef KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_TRUE_H_INCLUDED
#define KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_TRUE_H_INCLUDED

#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestAssertTrue : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testAssertTrue() {
		UT_ASSERT_TRUE(true);
	}

	void testAssertFalse() {
//		UT_ASSERT_TRUE(false);
	}
};

} /* namespace kernel */

#endif /* KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_TRUE_H_INCLUDED */
