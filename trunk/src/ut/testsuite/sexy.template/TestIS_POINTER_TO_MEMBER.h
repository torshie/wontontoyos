#ifndef KERNEL_SEXY_TEMPLATE_TEST_IS_POINTER_TO_MEMBER_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_TEST_IS_POINTER_TO_MEMBER_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include <sexy/IS_POINTER_TO_MEMBER.h>

namespace kernel {

class TestIS_POINTER_TO_MEMBER : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithNormalPointer() {
		UT_ASSERT_FALSE(IS_POINTER_TO_MEMBER<char*>::value);
	}

	void testWithFunctionPointer() {
		UT_ASSERT_FALSE(IS_POINTER_TO_MEMBER<void (*)>::value);
	}

	void testWithPointerToMember() {
		UT_ASSERT_TRUE(IS_POINTER_TO_MEMBER<void (TestCase::*)(void)>::value);
	}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_TEMPLATE_TEST_IS_POINTER_TO_MEMBER_H_INCLUDED */
