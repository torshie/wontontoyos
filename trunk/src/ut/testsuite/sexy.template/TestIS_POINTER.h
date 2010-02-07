#ifndef KERNEL_SEXY_TEMPLATE_TEST_IS_POINTER_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_TEST_IS_POINTER_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include <sexy/IS_POINTER.h>

namespace kernel {

class TestIS_POINTER : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithPointer() {
		UT_ASSERT_TRUE(IS_POINTER<void*>::value);
	}

	void testWithConstPointer() {
		UT_ASSERT_TRUE(IS_POINTER<const void*>::value);
	}

	void testWithNonPointer() {
		UT_ASSERT_FALSE(IS_POINTER<char>::value);
		UT_ASSERT_FALSE(IS_POINTER<void>::value);
	}

	void testWithReference() {
		UT_ASSERT_FALSE(IS_POINTER<char&>::value);
	}

	void testWithReferenceToPointer() {
		UT_ASSERT_FALSE(IS_POINTER<char*&>::value);
	}

	void testWithFunctionPointer() {
		UT_ASSERT_TRUE(IS_POINTER<void (*)(void)>::value);
	}

	void testWithPointerToMember() {
		UT_ASSERT_TRUE(IS_POINTER<void (TestCase::*)(void)>::value);
	}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_TEMPLATE_TEST_IS_POINTER_H_INCLUDED */
