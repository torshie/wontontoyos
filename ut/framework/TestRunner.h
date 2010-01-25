#ifndef KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED

#include <generic/getSingleInstance.h>
#include "TestSuite.h"
#include "TestResult.h"

namespace kernel {

class UnitTestingAssert;
/**
 * XXX Rewrite this class when kernel heap is ready
 */
class TestRunner {
	friend TestRunner& getSingleInstance<TestRunner>();
	friend class UnitTestingAssert;
public:
	void addTestSuite(TestSuite& suite, const char* name);
	void run(TestResult& result);

	/**
	 * Do not display any information when running test cases
	 */
	void keepQuiet() {
		quiet = true;
	}

	/**
	 * Display detailed information when running test cases
	 */
	void verbose() {
		quiet = false;
	}

	/**
	 * The implementation of the method will be generated the shell script
	 * "GenerateTestSuite.sh"
	 */
	void installTestSuite();

private:
	TestRunner(const TestRunner&);
	const TestRunner& operator = (const TestRunner&);

	enum {
		TEST_SUITE_MAX = 128
	};

	bool quiet;
	int suiteCount;
	TestSuite* testSuite[TEST_SUITE_MAX];
	const char* testSuiteName[TEST_SUITE_MAX];

	TestRunner() : suiteCount(0) {}
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED */
