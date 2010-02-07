#ifndef KERNEL_SEXY_TEMPLATE_TEST_IS_CLASS_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_TEST_IS_CLASS_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include <sexy/IS_CLASS.h>

namespace kernel {

class TestIS_CLASS : public TestCase {
	enum Enum {};
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithClass() {
		UT_ASSERT_TRUE(IS_CLASS<TestCase>::value);
	}

	void testWithInteger() {
		UT_ASSERT_FALSE(IS_CLASS<int>::value);
	}

	void testWithVoid() {
		UT_ASSERT_FALSE(IS_CLASS<void>::value);
	}

	void testWithEnum() {
		UT_ASSERT_FALSE(IS_CLASS<Enum>::value);
	}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_TEMPLATE_TEST_IS_CLASS_H_INCLUDED */
