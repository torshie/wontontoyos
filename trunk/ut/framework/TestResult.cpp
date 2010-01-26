#include "TestResult.h"
#include "Printer.h"

namespace kernel {

void TestResult::show() {
	Printer& console = getSingleInstance<Printer>();
	console << "Test result:\n"
			<< "Number Of Test Suites: " << suiteCount << "\n"
			<< "Number Of Test Cases: " << caseCount
			<< ", Failed: " << failedCase << "\n"
			<< "Number Of Test Points: " << testPointCount
			<< ", Failed: " << failedTestPoint << "\n"
			<< "Number Of Assertions: " << assertionCount
			<< ", Failed: " << failedAssertion << "\n";
}

} /* namespace kernel */
