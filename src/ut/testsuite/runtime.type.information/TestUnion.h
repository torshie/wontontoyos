#ifndef KERNEL_RUNTIME_TYPE_INFORMATION_TEST_UNION_H_INCLUDED
#define KERNEL_RUNTIME_TYPE_INFORMATION_TEST_UNION_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "cxx/rtti.h"

namespace kernel {

class TestUnion : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithSingleUnion() {
		union Union {
		};
		Union u;
		UT_ASSERT_EQUAL(typeid(u), typeid(Union));
	}

	void testWithTwoUnions() {
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

#endif /* KERNEL_RUNTIME_TYPE_INFORMATION_TEST_UNION_H_INCLUDED */
