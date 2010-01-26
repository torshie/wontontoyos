#ifndef KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED

#include "TestRunner.h"

namespace kernel {

class UnitTestingAssert {
public:
	static void assert(bool value, const char* file, int line,
			const char* expression);

	template<typename T>
	static void equal(const T& actual, const T& expected, const char* file,
			int line, const char* actualString,
			const char* expectedString) {
		TestRunner& runner = getSingleInstance<TestRunner>();
		if (actual == expected) {
			runner.assertionSucceeded();
		} else {
			runner.assertionFailed(file, line, actual, expectedString);
		}
	}
};

} /* namespace kernel */

#define UT_ASSERT(value) \
	::kernel::UnitTestingAssert::assert((value), __FILE__, __LINE__, \
			#value)

#define UT_ASSERT_EQUAL(actual, expected) \
	::kernel::UnitTestingAssert::equal((actual), (expected), __FILE__, \
			__LINE__, #actual, #expected)

#endif /* KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED */
