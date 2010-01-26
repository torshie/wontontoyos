#include "TestSuite.h"

namespace kernel {

void TestSuite::addTestCase(TestCase& tc, const char* name) {
	testCase[caseCount] = &tc;
	testCaseName[caseCount] = name;
	TestPoint point;
	const char* tmpName;
	int count = 0;
	while (tc.getTestPoint(point, tmpName)) {
		testPoint[caseCount][count] = point;
		testPointName[caseCount][count] = tmpName;
		++count;
	}
	testPointCount[caseCount] = count;
	++caseCount;
}

void TestSuite::run(TestResult& result) {
	for (int i = 0; i < caseCount; ++i) {
	}
}

} /* namespace kernel */
