#ifndef KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED

#include "TestSuite.h"
#include "TestResult.h"
#include "Message.h"
#include <generic/Utils.h>

namespace kernel {

class UnitTestingAssert;
class TestSuite;

class TestRunner {
	friend TestRunner& getSingleInstance<TestRunner>();
	friend class UnitTestingAssert;
public:
	void addTestSuite(TestSuite& suite, const char* name);
	void run(TestResult& result);

	void stopWhenFailed(bool b) {
		stop = b;
	}

private:
	TestRunner(const TestRunner&);
	const TestRunner& operator = (const TestRunner&);

	enum {
		MAX_TEST_SUITE = 32
	};

	int totalSuite;
	TestResult* result;
	bool stop;
	int totalAssertion;
	int failedAssertion;
	TestSuite* testSuite[MAX_TEST_SUITE];
	const char* testSuiteName[MAX_TEST_SUITE];


	// The implementation of the method will be generated by the shell script
	// "GenerateTestSuite.sh"
	void installTestSuite();

	void runTestSuite(TestSuite& suite);

	void runTestCase(TestSuite& suite, int testCaseId);

	TestRunner() : totalSuite(0), result(0), stop(false), totalAssertion(0), failedAssertion(0) {
		installTestSuite();
	}

	void prepareForTesting() {
		totalAssertion = 0;
		failedAssertion = 0;
	}

	void saveAssertionInformation() {
		result->totalAssertion += totalAssertion;
		result->failedAssertion += failedAssertion;
	}

	bool shouldStopTesting() const {
		return !isTestPointClean() && stop;
	}

	bool isTestPointClean() const {
		return failedAssertion == 0;
	}

	void gotTrueAssertion() {
		totalAssertion++;
	}

	void gotFalseAssertion(const char* file, int line,
			const char* expression) {
		failedAssertion++;
		totalAssertion++;
		Message::warning << Utils::basename(file) << ":" << line
				<< " ASSERT(" << expression << ")\n";
	}

	template<typename First, typename Second>
	void gotFalseEqualAssertion(const char* file, int line,
			const char* firstExpression, const char* secondExpression,
			const First& first, const Second& second) {
		failedAssertion++;
		totalAssertion++;
		Message::warning << Utils::basename(file) << ":" << line << " " << firstExpression
				<< "[" << first << "] == " << secondExpression << "[" << second << "]\n";
	}

	template<typename First, typename Second>
	void gotFalseUnequalAssertion(const char* file, int line,
			const char* firstExpression, const char* secondExpression,
			const First& first, const Second& second) {
		failedAssertion++;
		totalAssertion++;
		Message::warning << Utils::basename(file) << ":" << line << " " << firstExpression
				<< "[" << first << "] != " << secondExpression << "[" << second << "]\n";
	}
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_RUNNER_H_INCLUDED */
