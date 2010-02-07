#ifndef KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED

#include "TestRunner.h"
#include <generic/Memory.h>
#include <generic/Comparer.h>

namespace kernel {

class UnitTestingAssert {
public:
	static void assertTrue(bool value, const char* file, int line,
			const char* expression);

	template<typename First, typename Second>
	static void assertEqual(const First& actual, const Second& expected,
			const char* file, int line, const char* actualString,
			const char* expectedString) {
		TestRunner& runner = getSingleInstance<TestRunner>();
		if (Comparer<First, Second>::equal(actual, expected)) {
			runner.gotTrueAssertion();
		} else {
			runner.gotFalseEqualAssertion(file, line, actualString,
					expectedString);
		}
	}

	template<typename First, typename Second>
	static void assertUnequal(const First& first, const Second& second,
			const char* file, int line, const char* firstString,
			const char* secondString) {
		TestRunner& runner = getSingleInstance<TestRunner>();
		if (Comparer<First, Second>::unequal(first, second)) {
			runner.gotTrueAssertion();
		} else {
			runner.gotFalseUnequalAssertion(file, line, firstString,
					secondString);
		}
	}
};

} /* namespace kernel */

#define UT_ASSERT_TRUE(value) \
	::kernel::UnitTestingAssert::assertTrue((value), __FILE__, __LINE__, \
			#value)

#define UT_ASSERT_FALSE(value) UT_ASSERT_TRUE(!(value))

#define UT_ASSERT_EQUAL(actual, expected) \
	::kernel::UnitTestingAssert::assertEqual((actual), (expected), \
			__FILE__, __LINE__, #actual, #expected)

#define UT_ASSERT_UNEQUAL(first, second) \
	::kernel::UnitTestingAssert::assertUnequal((first), (second), \
			__FILE__, __LINE__, #first, #second)

#endif /* KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED */
