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

	void testEqualNumbers() {
//		UT_ASSERT_UNEQUAL(1, 1);
	}

	void testNotEqualNumbers() {
		UT_ASSERT_UNEQUAL(1, 2);
	}

	void testEqualIntegerVariableAndLiteral() {
//		int i = 1;
//		UT_ASSERT_UNEQUAL(i, 1);
	}

	void testEqualStringLiterals() {
//		UT_ASSERT_UNEQUAL("Hello", "Hello");
	}

	void testNotEqualStringLiterals() {
		UT_ASSERT_UNEQUAL("Hello", "World");
	}

	void testEqualCharArrays() {
//		char firstHello[] = "Hello";
//		char secondHello[] = "Hello";
//		UT_ASSERT_UNEQUAL(firstHello, secondHello);
	}

	void testNotEqualCharArrays() {
		char hello[] = "Hello";
		char world[] = "World";
		UT_ASSERT_UNEQUAL(hello, world);
	}

	void testEqualCharArrayAndStringLiteral() {
//		char hello[] = "Hello";
//		UT_ASSERT_UNEQUAL(hello, "Hello");
	}

	void testDifferentSizedEqualCharArrays() {
//		char firstHello[10] = "Hello";
//		char secondHello[20] = "Hello";
//		UT_ASSERT_UNEQUAL(firstHello, secondHello);
	}
};

} /* namespace kernel */
