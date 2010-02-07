#ifndef KERNEL_SEXY_TEMPLATE_TEST_IS_REFERENCE_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_TEST_IS_REFERENCE_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include <sexy/IS_REFERENCE.h>

namespace kernel {

class TestIS_REFERENCE : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithReference() {
		UT_ASSERT_TRUE(IS_REFERENCE<char&>::value);
	}

	void testWithNonReference() {
		UT_ASSERT_FALSE(IS_REFERENCE<char>::value);
	}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_TEMPLATE_TEST_IS_REFERENCE_H_INCLUDED */
