#include "ut/framework/UnitTesting.h"
#include <cxx/typeinfo.h>

namespace kernel {

class TestBasicType : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testIntegeralTypes() {
		signed char sc = 0;
		UT_ASSERT_EQUAL(typeid(sc), typeid(signed char));
		unsigned char uc = 0;
		UT_ASSERT_EQUAL(typeid(uc), typeid(unsigned char));
		UT_ASSERT_UNEQUAL(typeid(uc), typeid(sc));

		short s = 0;
		UT_ASSERT_EQUAL(typeid(s), typeid(short));
		unsigned short us = 0;
		UT_ASSERT_EQUAL(typeid(us), typeid(unsigned short));
		UT_ASSERT_UNEQUAL(typeid(s), typeid(us));

		int i = 0;
		UT_ASSERT_EQUAL(typeid(i), typeid(int));
		unsigned ui = 0;
		UT_ASSERT_EQUAL(typeid(ui), typeid(unsigned int));
		UT_ASSERT_UNEQUAL(typeid(ui), typeid(i));

		long l = 0;
		UT_ASSERT_EQUAL(typeid(l), typeid(long));
		unsigned long ul = 0;
		UT_ASSERT_EQUAL(typeid(ul), typeid(unsigned long));
		UT_ASSERT_UNEQUAL(typeid(ul), typeid(l));

		long long ll = 0;
		UT_ASSERT_EQUAL(typeid(ll), typeid(long long));
		unsigned long long ull = 0;
		UT_ASSERT_EQUAL(typeid(ull), typeid(unsigned long long));
		UT_ASSERT_UNEQUAL(typeid(ull), typeid(ll));
	}

	void testVoid() {
		UT_ASSERT_EQUAL(typeid(void), typeid(void));
		UT_ASSERT_UNEQUAL(typeid(void), typeid(int));
	}

	void testConstPointer() {
		char* p = 0;
		const char* q = 0;
		UT_ASSERT_UNEQUAL(typeid(p), typeid(q));
	}
};

} /* namespace kernel */
