#ifndef KERNEL_SEXY_TEMPLATE_TEST_IS_SIGNED_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_TEST_IS_SIGNED_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include <sexy/IS_SIGNED.h>

namespace kernel {

class TestIS_SIGNED : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testSignedTypes() {
		UT_ASSERT_TRUE(IS_SIGNED<signed char>::value);
		UT_ASSERT_TRUE(IS_SIGNED<short>::value);
		UT_ASSERT_TRUE(IS_SIGNED<int>::value);
		UT_ASSERT_TRUE(IS_SIGNED<long>::value);
		UT_ASSERT_TRUE(IS_SIGNED<long long>::value);
	}

	void testUnsignedTypes() {
		UT_ASSERT_FALSE(IS_SIGNED<unsigned char>::value);
		UT_ASSERT_FALSE(IS_SIGNED<unsigned short>::value);
		UT_ASSERT_FALSE(IS_SIGNED<unsigned int>::value);
		UT_ASSERT_FALSE(IS_SIGNED<unsigned long>::value);
		UT_ASSERT_FALSE(IS_SIGNED<unsigned long long>::value);
	}

	void testNonIntegeralTypes() {
		UT_ASSERT_FALSE(IS_SIGNED<bool>::value);
		UT_ASSERT_FALSE(IS_SIGNED<void>::value);
		UT_ASSERT_FALSE(IS_SIGNED<void*>::value);
	}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_TEMPLATE_TEST_IS_SIGNED_H_INCLUDED */
