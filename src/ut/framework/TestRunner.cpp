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
	Printer& console = getSingleInstance<Printer> ();
	result = &r;
	for (int i = 0; i < totalSuite; ++i) {
		if (!quiet) {
			console << "Running test suite " << testSuiteName[i] << "\n";
		}
		result->totalSuite++;
		testSuite[i]->run(*this);
	}
}

} /* namespace kernel */
