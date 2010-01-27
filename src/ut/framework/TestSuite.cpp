#include "TestSuite.h"
#include "Printer.h"
#include "TestRunner.h"

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

void TestSuite::run(TestRunner& runner) {
	Printer& console = getSingleInstance<Printer>();
	for (int i = 0; i < caseCount; ++i) {
		if (!runner.isQuiet()) {
			console << "    Running test case " << testCaseName[i] << "\n";
		}
		runTestCase(i, runner);
	}
}

void TestSuite::runTestCase(int index, TestRunner& runner) {
	Printer& console = getSingleInstance<Printer>();
	runner.initialize();
	for (int i = 0; i < testPointCount[index]; ++i) {
		if (!runner.isQuiet()) {
			console << "        " << testPointName[index][i];
		}
		testCase[index]->setUp();
		(testCase[index]->*testPoint[index][i])();
		testCase[index]->tearDown();

		if (runner.testPointPassed()) {
			if (!runner.isQuiet()) {
				console << "------- PASSED\n";
			}
		} else {
			if (!runner.isQuiet()) {
				console << "-------- FAILED\n";
			}
			if (runner.shouldStopTesting()) {
				break;
			}
		}
		runner.reset();
	}
	runner.finalize();
}

} /* namespace kernel */
