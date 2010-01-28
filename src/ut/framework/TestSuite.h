#ifndef KERNEL_UT_FRAMEWORK_TEST_SUITE_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_SUITE_H_INCLUDED

#include "TestCase.h"

namespace kernel {

class TestRunner;

class TestSuite {
	friend class TestRunner;
public:
	TestSuite() : totalCase(0) {}

	void addTestCase(TestCase& testCase, const char* testCaseName);

private:
	enum {
		MAX_TEST_CASE = 128,
		MAX_TEST_POINT = 32
	};

	int totalCase;
	TestCase* testCase[MAX_TEST_CASE];
	const char* testCaseName[MAX_TEST_CASE];
	int totalTestPoint[MAX_TEST_CASE];
	TestCase::TestPoint testPoint[MAX_TEST_CASE][MAX_TEST_POINT];
	const char* testPointName[MAX_TEST_CASE][MAX_TEST_POINT];
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_SUITE_H_INCLUDED */
