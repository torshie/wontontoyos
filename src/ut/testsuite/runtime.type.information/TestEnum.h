#ifndef KERNEL_RUNTIME_TYPE_INFORMATION_TEST_ENUM_H_INCLUDED
#define KERNEL_RUNTIME_TYPE_INFORMATION_TEST_ENUM_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "cxx/rtti.h"

namespace kernel {

class TestEnum : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithSingleEnumType() {
		enum Enumeration {
			A, B
		};
		UT_ASSERT_EQUAL(typeid(A), typeid(Enumeration));
		UT_ASSERT_EQUAL(typeid(A), typeid(B));
		int i = B;
		UT_ASSERT_UNEQUAL(typeid(i), typeid(B));
	}

	void testWithTwoEnum() {
		enum FirstEnum {
			A, B
		};

		enum SecondEnum {
			C, D
		};

		UT_ASSERT_UNEQUAL(typeid(FirstEnum), typeid(SecondEnum));
		UT_ASSERT_UNEQUAL(typeid(A), typeid(C));
	}

	void testAnonymousEnum() {
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

#endif /* KERNEL_RUNTIME_TYPE_INFORMATION_TEST_ENUM_H_INCLUDED */
