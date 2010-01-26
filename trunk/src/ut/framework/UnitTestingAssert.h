#ifndef KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED

#include "TestRunner.h"
#include <generic/Memory.h>

namespace kernel {

class UnitTestingAssert {
public:
	static void assert(bool value, const char* file, int line,
			const char* expression);

	template<typename T>
	static void assertEqual(const T& actual, const T& expected,
			const char* file, int line, const char* actualString,
			const char* expectedString) {
		TestRunner& runner = getSingleInstance<TestRunner>();
		if (equal(actual, expected)) {
			runner.assertionSucceeded();
		} else {
			runner.assertionFailed(file, line, actualString,
					expectedString);
		}
	}

private:
	template<typename T>
	static bool equal(const T& a, const T& b) {
		return a == b;
	}
};

template<>
inline bool UnitTestingAssert::equal<const char*>(const char* const& a,
		const char* const& b) {
	return Memory::strcmp(a, b) == 0;
}

} /* namespace kernel */

#define UT_ASSERT(value) \
	::kernel::UnitTestingAssert::assert((value), __FILE__, __LINE__, \
			#value)

#define UT_ASSERT_EQUAL(actual, expected) \
	::kernel::UnitTestingAssert::assertEqual((actual), (expected), \
			__FILE__, __LINE__, #actual, #expected)

#endif /* KERNEL_UT_FRAMEWORK_UNIT_TESTING_ASSERT_H_INCLUDED */
