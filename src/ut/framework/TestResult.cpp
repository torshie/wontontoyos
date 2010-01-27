#include "TestResult.h"
#include "Printer.h"

namespace kernel {

void TestResult::show() {
	Printer& console = getSingleInstance<Printer>();
	console << "Test result:\n"
			<< "Number Of Test Suites: " << totalSuite << "\n"
			<< "Number Of Test Cases: " << totalCase
			<< ", Failed: " << failedCase << "\n"
			<< "Number Of Test Points: " << totalTestPoint
			<< ", Failed: " << failedTestPoint << "\n"
			<< "Number Of Assertions: " << totalAssertion
			<< ", Failed: " << failedAssertion << "\n";
}

} /* namespace kernel */
