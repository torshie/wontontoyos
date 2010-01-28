#include "TestRunner.h"
#include "Printer.h"

namespace kernel {

void TestRunner::addTestSuite(TestSuite& suite,
		const char* name) {
	testSuite[totalSuite] = &suite;
	testSuiteName[totalSuite] = name;
	++totalSuite;
}

void TestRunner::run(TestResult& r) {
	result = &r;
	for (int suiteId = 0; suiteId < totalSuite; ++suiteId) {
		message << "Running test suite " << testSuiteName[suiteId] << "\n";
		result->totalSuite++;
		runTestSuite(*(testSuite[suiteId]));
	}
}


void TestRunner::runTestSuite(TestSuite& suite) {
	for (int testCaseId = 0; testCaseId < suite.totalCase; ++testCaseId) {
		message << "    Running test case "
				<< suite.testCaseName[testCaseId] << "\n";
		runTestCase(suite, testCaseId);
	}
}

void TestRunner::runTestCase(TestSuite& suite, int testCaseId) {
	for (int testPointId = 0; testPointId < suite.totalTestPoint[testCaseId];
			++testPointId) {
		prepareForTesting();

		message << "        " << suite.testPointName[testCaseId][testPointId];
		suite.testCase[testCaseId]->setUp();
		(suite.testCase[testCaseId]->*suite.testPoint[testCaseId][testPointId])();
		suite.testCase[testCaseId]->tearDown();

		if (isTestPointClean()) {
			message << "-------- PASS\n";
		} else {
			message << "-------- FAIL\n";
			if (shouldStopTesting()) {
				break;
			}
		}

		saveTestingResult();
	}
}

} /* namespace kernel */
