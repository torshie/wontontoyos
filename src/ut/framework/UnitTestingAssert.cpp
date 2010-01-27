#include "UnitTestingAssert.h"

namespace kernel {

void UnitTestingAssert::assert(bool value, const char* file, int line,
		const char* expression) {
	TestRunner& runner = getSingleInstance<TestRunner>();
	if (value) {
		runner.assertionSucceeded();
	} else {
		runner.assertionFailed(file, line, expression);
	}
}

} /* namespace kernel */
