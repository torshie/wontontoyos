#ifndef KERNEL_UNIT_TEST_FRAMEWORK_TEST_METHOD_CALL_H_INCLUDED
#define KERNEL_UNIT_TEST_FRAMEWORK_TEST_METHOD_CALL_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "Printer.h"

namespace kernel {

class TestMethodCall : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testMethodCall() {
		Printer& console = getSingleInstance<Printer>();
		console << "Happy Testing :)";
	}
};

} /* namespace kernel */

#endif /* KERNEL_UNIT_TEST_FRAMEWORK_TEST_METHOD_CALL_H_INCLUDED */
