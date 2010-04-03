#include "ut/framework/UnitTesting.h"
#include "cxx/typeinfo.h"

namespace kernel {

class TestUnion : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testSingleUnion() {
		union Union {
		};
		Union u;
		UT_ASSERT_EQUAL(typeid(u), typeid(Union));
	}

	void testTwoUnions() {
		union FirstUnion {
		};
		union SecondUnion {
		};
		UT_ASSERT_UNEQUAL(typeid(FirstUnion), typeid(SecondUnion));
	}

	void testAnonymousUnion() {
		union {
		} u;
		union {
		} v;
		UT_ASSERT_UNEQUAL(typeid(u), typeid(v));
	}
};

} /* namespace kernel */
