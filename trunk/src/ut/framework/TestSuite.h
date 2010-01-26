#ifndef KERNEL_UT_FRAMEWORK_TEST_SUITE_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_SUITE_H_INCLUDED

#include "TestCase.h"

namespace kernel {

class TestRunner;

class TestSuite {
public:
	void addTestCase(TestCase& testCase, const char* testCaseName);
	void run(TestRunner& runner);

private:
	typedef void (TestCase::*TestPoint)(void);
	enum {
		TEST_CASE_MAX = 8,
		TEST_POINT_MAX = 32
	};

	int caseCount;
	TestCase* testCase[TEST_CASE_MAX];
	const char* testCaseName[TEST_CASE_MAX];
	int testPointCount[TEST_CASE_MAX];
	TestPoint testPoint[TEST_CASE_MAX][TEST_POINT_MAX];
	const char* testPointName[TEST_CASE_MAX][TEST_POINT_MAX];

	void runTestCase(int index, TestRunner& runner);
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_SUITE_H_INCLUDED */
