#ifndef KERNEL_UNIT_TESTING_FRAMEWORK_TEST_WITH_EMPTY_TEST_CASE_H_INCLUDED
#define KERNEL_UNIT_TESTING_FRAMEWORK_TEST_WITH_EMPTY_TEST_CASE_H_INCLUDED

#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestWithEmptyTestCase : public TestCase {
public:
	bool getTestPoint(TestPoint& point, const char*& name);
};

} /* namespace kernel */

#endif
