#include "UnitTestingAssert.h"

namespace kernel {

void UnitTestingAssert::assertTrue(bool value, const char* file, int line,
		const char* expression) {
	TestRunner& runner = getSingleInstance<TestRunner>();
	if (value) {
		runner.gotTrueAssertion();
	} else {
		runner.gotFalseAssertion(file, line, expression);
	}
}

} /* namespace kernel */
