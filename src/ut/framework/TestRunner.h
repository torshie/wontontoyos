#ifndef KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED

#include "TestSuite.h"
#include "TestResult.h"
#include "Printer.h"

namespace kernel {

class UnitTestingAssert;
class TestSuite;
/**
 * XXX Rewrite this class when kernel heap is ready
 */
class TestRunner {
	/**
	 * XXX Too many friends, refactor the code
	 */
	friend TestRunner& getSingleInstance<TestRunner>();
	friend class UnitTestingAssert;
	friend class TestSuite;
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

	bool isQuiet() {
		return quiet;
	}

	void stopWhenFailed(bool b) {
		stop = b;
	}

	/**
	 * The implementation of the method will be generated by the shell script
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
	int totalSuite;
	TestResult* result;
	bool stop;
	int totalAssertion;
	int failedAssertion;
	TestSuite* testSuite[TEST_SUITE_MAX];
	const char* testSuiteName[TEST_SUITE_MAX];

	TestRunner() : quiet(false), totalSuite(0), result(0), stop(false),
			totalAssertion(0),
			failedAssertion(0) {}

	void reset() {
		failedAssertion = 0;
		totalAssertion = 0;
	}

	void finalize() {
		result->totalCase++;
		result->totalAssertion += totalAssertion;
		result->failedAssertion += failedAssertion;
	}

	/**
	 * XXX This method is in fact empty! In the sake of completeness we
	 * add this method, since we have finalize() ???
	 */
	void initialize() {
	}

	bool shouldStopTesting() const {
		return failedAssertion > 0 && stop;
	}

	bool testPointPassed() const {
		return failedAssertion == 0;
	}

	void assertionSucceeded() {
		result->totalAssertion++;
	}

	void showFailedMessage(const char* file, int line,
			const char* expression) {
		Printer& console = getSingleInstance<Printer>();
		console << file << ":" << line << " " << expression << " FAILED\n";
	}

	void showFailedMessage(const char* file, int line, const char* actual,
			const char* expected) {
		Printer& console = getSingleInstance<Printer>();
		console << file << ":" << line << " " << actual << " == "
				<< expected << " FAILED\n";
	}

	void assertionFailed(const char* file, int line,
			const char* expression) {
		result->failedAssertion++;
		result->totalAssertion++;
		if (!isQuiet()) {
			showFailedMessage(file, line, expression);
		}
	}

	void assertionFailed(const char* file, int line,
				const char* actual, const char* expected) {
			result->failedAssertion++;
			result->totalAssertion++;
			if (!isQuiet()) {
				showFailedMessage(file, line, actual, expected);
			}
		}
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED */
