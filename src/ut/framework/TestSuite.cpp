#include "TestSuite.h"
#include "Printer.h"
#include "TestRunner.h"

namespace kernel {

void TestSuite::addTestCase(TestCase& tc, const char* name) {
	testCase[totalCase] = &tc;
	testCaseName[totalCase] = name;
	TestCase::TestPoint point;
	const char* tmpName;
	int count = 0;
	while (tc.getTestPoint(point, tmpName)) {
		testPoint[totalCase][count] = point;
		testPointName[totalCase][count] = tmpName;
		++count;
	}
	totalTestPoint[totalCase] = count;
	++totalCase;
}

} /* namespace kernel */
