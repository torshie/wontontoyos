#include "ut/framework/UnitTesting.h"
#include <cxx/typeinfo.h>

namespace kernel {

class TestClassWithVirtualMethod : public TestCase {
	class Base {
	public:
		virtual ~Base() {}
	};

	class First : public Base {};
	class Second : public Base {};

	First first;
	Second second;
	Base* base[2];
public:
	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		base[0] = &first;
		base[1] = &second;
	}

	void tearDown() {
		base[0] = 0;
		base[1] = 0;
	}

	void testTypeIdOfClasses() {
		UT_ASSERT_UNEQUAL(typeid(First), typeid(Second));
		UT_ASSERT_UNEQUAL(typeid(Base), typeid(First));
		UT_ASSERT_UNEQUAL(typeid(Base), typeid(Second));
	}

	void testPointDereference() {
		UT_ASSERT_EQUAL(typeid(First), typeid(*base[0]));
		UT_ASSERT_EQUAL(typeid(Second), typeid(*base[1]));
		UT_ASSERT_UNEQUAL(typeid(*base[0]), typeid(*base[1]));
	}

	void testReference() {
		Base& a = first;
		Base& b = second;
		UT_ASSERT_UNEQUAL(typeid(a), typeid(b));
		UT_ASSERT_EQUAL(typeid(a), typeid(First));
		UT_ASSERT_EQUAL(typeid(b), typeid(Second));
	}
};

} /* namespace kernel */
