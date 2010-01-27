#ifndef TEST_FRAMEWORK_H_INCLUDED
#define TEST_FRAMEWORK_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "Printer.h"
#include <generic/getSingleInstance.h>

namespace kernel {

/**
 * Test whether the unit testing framework can work correctly
 */
class TestFramework : public TestCase {
public:
	bool getTestPoint(TestPoint& point, const char*& name);

	void setUp() {
		Printer& console = getSingleInstance<Printer>();
		console << "TestFramework::setUp()\n";
	}

	void tearDown() {
		Printer& console = getSingleInstance<Printer>();
		console << "TestFramework::tearDown()\n";
	}

	void testMethodCall() {
		Printer& console = getSingleInstance<Printer>();
		console << "TestFramework::testMethodCall()\n";
	}

	void testSimpleAssert() {
		UT_ASSERT(true);
	}

	void testAssertEqual() {
		UT_ASSERT_EQUAL(1, 1);
		UT_ASSERT_EQUAL(1, 2);
	}
};

}

#endif

