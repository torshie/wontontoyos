#ifndef KERNEL_UT_FRAMEWORK_TEST_RESULT_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_RESULT_H_INCLUDED

namespace kernel {

class TestResult {
public:
	TestResult() : suiteCount(0), caseCount(0), failedCase(0), testPointCount(0),
			failedTestPoint(0), assertionCount(0), failedAssertion(0) {
	}

	/**
	 * Show the test result to user.
	 */
	void show();

	int suiteCount;
	int caseCount;
	int failedCase;
	int testPointCount;
	int failedTestPoint;
	int assertionCount;
	int failedAssertion;
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_RESULT_H_INCLUDED */
