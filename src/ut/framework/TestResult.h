#ifndef KERNEL_UT_FRAMEWORK_TEST_RESULT_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_RESULT_H_INCLUDED

namespace kernel {

class TestResult {
public:
	TestResult() : suiteCount(0), totalCase(0), failedCase(0),
			totalTestPoint(0), failedTestPoint(0), totalAssertion(0),
			failedAssertion(0) {}

	/**
	 * Show the test result to user.
	 */
	void show();

	int suiteCount;
	int totalCase;
	int failedCase;
	int totalTestPoint;
	int failedTestPoint;
	int totalAssertion;
	int failedAssertion;
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_RESULT_H_INCLUDED */
