#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestNewDelete : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testNew() {
		int* value = new int(0x900D);
		UT_ASSERT_EQUAL(*value, 0x900D);

		delete value;
	}

	void testMerge() {
		int* first = new int;
		int* second = new int;
		delete first;
		delete second;

		int* third = new int;
		UT_ASSERT_EQUAL(first, third);

		delete third;
	}
};

} // namespace kernel
