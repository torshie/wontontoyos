#ifndef KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_UNEQUAL_H_INCLUDED
#define KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_UNEQUAL_H_INCLUDED

#include "ut/framework/UnitTesting.h"

namespace kernel {

/**
 * XXX This is really evil, the body of the class is just copied from
 * TestAssertEqual and change all the UT_ASSERT_EQUAL to
 * UT_ASSERT_UNEQUAL!
 */
class TestAssertUnequal : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithEqualNumbers() {
//		UT_ASSERT_UNEQUAL(1, 1);
	}

	void testWithNotEqualNumbers() {
		UT_ASSERT_UNEQUAL(1, 2);
	}

	void testWithEqualIntegerVariableAndLiteral() {
//		int i = 1;
//		UT_ASSERT_UNEQUAL(i, 1);
	}

	void testWithEqualStringLiterals() {
//		UT_ASSERT_UNEQUAL("Hello", "Hello");
	}

	void testWithNotEqualStringLiterals() {
		UT_ASSERT_UNEQUAL("Hello", "World");
	}

	void testWithEqualCharArrays() {
//		char firstHello[] = "Hello";
//		char secondHello[] = "Hello";
//		UT_ASSERT_UNEQUAL(firstHello, secondHello);
	}

	void testWithNotEqualCharArrays() {
		char hello[] = "Hello";
		char world[] = "World";
		UT_ASSERT_UNEQUAL(hello, world);
	}

	void testWithEqualCharArrayAndStringLiteral() {
//		char hello[] = "Hello";
//		UT_ASSERT_UNEQUAL(hello, "Hello");
	}

	void testWithDifferentSizedEqualCharArrays() {
//		char firstHello[10] = "Hello";
//		char secondHello[20] = "Hello";
//		UT_ASSERT_UNEQUAL(firstHello, secondHello);
	}
};

} /* namespace kernel */

#endif /* KERNEL_UNIT_TESTING_FRAMEWORK_TEST_ASSERT_UNEQUAL_H_INCLUDED */
