#ifndef KERNEL_RUNTIME_TYPE_INFORMATION_TEST_POD_CLASS_H_INCLUDED
#define KERNEL_RUNTIME_TYPE_INFORMATION_TEST_POD_CLASS_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "cxx/rtti.h"

namespace kernel {

class TestPODClass : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testSingleClass() {
		class Class {};
		Class c, d;
		UT_ASSERT_EQUAL(typeid(c), typeid(d));
		UT_ASSERT_EQUAL(typeid(c), typeid(Class));
		UT_ASSERT_UNEQUAL(typeid(c), typeid(int));
	}

	void testTwoClasses() {
		class First {};
		class Second {};
		First a;
		Second b;
		UT_ASSERT_UNEQUAL(typeid(a), typeid(b));
		UT_ASSERT_UNEQUAL(typeid(First), typeid(Second));
	}
};

} /* namespace kernel */

#endif /* KERNEL_RUNTIME_TYPE_INFORMATION_TEST_POD_CLASS_H_INCLUDED */
