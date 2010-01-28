#ifndef KERNEL_UNIT_TESTING_FRAMEWORK_TEST_SETUP_AND_TEARDOWN_H_INCLUDED
#define KERNEL_UNIT_TESTING_FRAMEWORK_TEST_SETUP_AND_TEARDOWN_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "Printer.h"

namespace kernel {

class TestSetUpAndTearDown : public TestCase {
public:
	bool getTestPoint(TestPoint& point, const char*& name);
	void setUp() {
		Printer& console = getSingleInstance<Printer>();
		console << " setUp()";
	}

	void tearDown() {
		Printer& console = getSingleInstance<Printer>();
		console << " tearDown()";
	}

	/**
	 * This function is used to make setUp & tearDown get called
	 */
	void testNothing() {}
};

} /* namespace kernel */

#endif
