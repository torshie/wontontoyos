#include "ut/framework/UnitTesting.h"
#include <generic/OFFSET_OF.h>
#include <generic/type.h>

namespace kernel {

class TestOFFSET_OF : public TestCase {
	template<typename Member> class Outer {
	public:
		Member outer;
		struct Inner {
			Member first;
			Member second;
		} __attribute__((packed));
	} __attribute__((packed));

public:
	bool getTestPoint(TestPoint&, const char*&);

	void testPlainOldData() {
		struct T {
			int a, b;
		} __attribute__((packed));

		UT_ASSERT_EQUAL(OFFSET_OF(T, a), 0);
		UT_ASSERT_EQUAL(OFFSET_OF(T, b), sizeof(int));
	}

	void testComplexSyntax() {
		UT_ASSERT_EQUAL(OFFSET_OF(Outer<int>::Inner, first), 0);
		UT_ASSERT_EQUAL(OFFSET_OF(Outer<int>::Inner, second), sizeof(int));
		UT_ASSERT_EQUAL(OFFSET_OF(Outer<Address>::Inner, second), sizeof(Address));
	}
};

} // namespace kernel
