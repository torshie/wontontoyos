#include "ut/framework/UnitTesting.h"
#include <generic/Utils.h>

namespace kernel {

class TestStrncpy : public TestCase {
	const char* source;
public:
	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		source = "hello";
	}

	void testSimpleCopy() {
		char buffer[32];
		Size size = Utils::strncpy(buffer, source, sizeof(buffer));
		UT_ASSERT_EQUAL(buffer, source);
		UT_ASSERT_EQUAL(size, 5);
	}

	void testOneByteArray() {
		char buffer[1];
		Size size = Utils::strncpy(buffer, source, sizeof(buffer));
		UT_ASSERT_EQUAL(buffer, "");
		UT_ASSERT_EQUAL(size, 0);
	}

	void testTwoByteArray() {
		char buffer[2];
		Size size = Utils::strncpy(buffer, source, sizeof(buffer));
		UT_ASSERT_EQUAL(buffer, "h");
		UT_ASSERT_EQUAL(size, 1);
	}

	void testEmptyArray() {
		char buffer[1];
		Size size = Utils::strncpy(buffer, source, 0);
		UT_ASSERT_EQUAL(size, 0);
	}
};

} /* namespace kernel */
