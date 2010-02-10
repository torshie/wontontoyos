#ifndef KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_EQUAL_H_INCLUDED
#define KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_EQUAL_H_INCLUDED

#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestAssertEqual : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithEqualNumbers() {
		UT_ASSERT_EQUAL(1, 1);
	}

	void testWithNotEqualNumbers() {
//		UT_ASSERT_EQUAL(1, 2);
	}

	void testWithEqualIntegerVariableAndLiteral() {
		int i = 1;
		UT_ASSERT_EQUAL(i, 1);
	}

	void testWithEqualStringLiterals() {
		UT_ASSERT_EQUAL("Hello", "Hello");
	}

	void testWithNotEqualStringLiterals() {
//		UT_ASSERT_EQUAL("Hello", "World");
	}

	void testWithEqualCharArrays() {
		char firstHello[] = "Hello";
		char secondHello[] = "Hello";
		UT_ASSERT_EQUAL(firstHello, secondHello);
	}

	void testWithNotEqualCharArrays() {
//		char hello[] = "Hello";
//		char world[] = "World";
//		UT_ASSERT_EQUAL(hello, world);
	}

	void testWithEqualCharArrayAndStringLiteral() {
		char hello[] = "Hello";
		UT_ASSERT_EQUAL(hello, "Hello");
	}

	void testWithDifferentSizedEqualCharArrays() {
		char firstHello[10] = "Hello";
		char secondHello[20] = "Hello";
		UT_ASSERT_EQUAL(firstHello, secondHello);
	}

	void testWithDifferentTypeOfIntegers() {
		short s = -1;
		int i = -1;
		UT_ASSERT_EQUAL(s, i);
	}
};

} /* namespace kernel */

#endif /* KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_EQUAL_H_INCLUDED */
