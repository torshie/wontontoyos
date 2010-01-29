#ifndef KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED

#include "TestRunner.h"
#include <generic/Memory.h>
#include <generic/Comparer.h>

namespace kernel {

class UnitTestingAssert {
public:
	static void assert(bool value, const char* file, int line,
			const char* expression);

	template<typename First, typename Second>
	static void assertEqual(const First& actual, const Second& expected,
			const char* file, int line, const char* actualString,
			const char* expectedString) {
		TestRunner& runner = getSingleInstance<TestRunner>();
		if (Comparer<First, Second>::equal(actual, expected)) {
			runner.gotTrueAssertion();
		} else {
			runner.gotFalseAssertion(file, line, actualString,
					expectedString);
		}
	}
};

} /* namespace kernel */

#define UT_ASSERT(value) \
	::kernel::UnitTestingAssert::assert((value), __FILE__, __LINE__, \
			#value)

#define UT_ASSERT_EQUAL(actual, expected) \
	::kernel::UnitTestingAssert::assertEqual((actual), (expected), \
			__FILE__, __LINE__, #actual, #expected)

#endif /* KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED */
