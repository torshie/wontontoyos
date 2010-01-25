#include "TestRunner.h"
#include "Printer.h"

namespace kernel {

void TestRunner::addTestSuite(TestSuite& suite,
		const char* name) {
	testSuite[suiteCount] = &suite;
	testSuiteName[suiteCount] = name;
	++suiteCount;
}

void TestRunner::run(TestResult& result) {
	Printer& console = getSingleInstance<Printer> ();
	for (int i = 0; i < suiteCount; ++i) {
		if (!quiet) {
			console << "Running test suite: " << testSuiteName[i] << "\n";
		}
		testSuite[i]->run(result);
	}
}

} /* namespace kernel */
