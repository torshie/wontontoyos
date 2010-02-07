#ifndef KERNEL_SEXY_TEMPLATE_TEST_IS_ARRAY_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_TEST_IS_ARRAY_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include <sexy/IS_ARRAY.h>

namespace kernel {

class TestIS_ARRAY : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithInteger() {
		UT_ASSERT_FALSE(IS_ARRAY<int>::value);
	}

	void testWithVoid() {
		UT_ASSERT_FALSE(IS_ARRAY<void>::value);
	}

	void testWithArray() {
		UT_ASSERT_TRUE(IS_ARRAY<char[1]>::value);
	}

	void testWithEmptyArray() {
		UT_ASSERT_TRUE(IS_ARRAY<char[]>::value);
	}

	void testWithZeroLengthArray() {
		UT_ASSERT_TRUE(IS_ARRAY<char[0]>::value);
	}

	void testWithPointer() {
		UT_ASSERT_FALSE(IS_ARRAY<char*>::value);
	}
};

}

#endif /* KERNEL_SEXY_TEMPLATE_TEST_IS_ARRAY_H_INCLUDED */
