#include "ut/framework/UnitTesting.h"
#include "cxx/rtti.h"

namespace kernel {

class TestEnum : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testSingleEnum() {
		enum Enumeration {
			A, B
		};
		UT_ASSERT_EQUAL(typeid(A), typeid(Enumeration));
		UT_ASSERT_EQUAL(typeid(A), typeid(B));
		int i = B;
		UT_ASSERT_UNEQUAL(typeid(i), typeid(B));
	}

	void testTwoEnums() {
		enum FirstEnum {
			A, B
		};

		enum SecondEnum {
			C, D
		};

		UT_ASSERT_UNEQUAL(typeid(FirstEnum), typeid(SecondEnum));
		UT_ASSERT_UNEQUAL(typeid(A), typeid(C));
	}

	void testAnonymousEnums() {
		enum {
			A, B
		};
		enum {
			C, D
		};

		UT_ASSERT_EQUAL(typeid(A), typeid(B));
		UT_ASSERT_UNEQUAL(typeid(A), typeid(C));
	}
};

} /* namespace kernel */
