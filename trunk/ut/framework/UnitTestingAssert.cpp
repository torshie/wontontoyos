#include "UnitTestingAssert.h"
#include "TestRunner.h"

namespace kernel {

void UnitTestingAssert::assert(bool value, const char* file, int line,
		const char* expression) {
	TestRunner& runner = getSingleInstance<TestRunner>();
}

} /* namespace kernel */
