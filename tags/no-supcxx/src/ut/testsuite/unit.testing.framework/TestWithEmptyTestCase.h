#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestWithEmptyTestCase : public TestCase {
public:
	bool getTestPoint(TestPoint& point, const char*& name);
};

} /* namespace kernel */
