#ifndef KERNEL_SEXY_TEMPLATE_IS_ENUM_H_INCLUDED
#define KERNEL_SEXY_TEMPLATE_IS_ENUM_H_INCLUDED

#include <sexy/IS_ENUM.h>
#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestIS_ENUM : public TestCase {
	enum NamedEnum {};
	typedef enum {} AnonymousEnum;
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testWithIntegerTypes() {
		UT_ASSERT_FALSE(IS_ENUM<signed char>::value);
		UT_ASSERT_FALSE(IS_ENUM<short>::value);
		UT_ASSERT_FALSE(IS_ENUM<int>::value);
		UT_ASSERT_FALSE(IS_ENUM<long>::value);
		UT_ASSERT_FALSE(IS_ENUM<long long>::value);

		UT_ASSERT_FALSE(IS_ENUM<unsigned char>::value);
		UT_ASSERT_FALSE(IS_ENUM<unsigned short>::value);
		UT_ASSERT_FALSE(IS_ENUM<unsigned int>::value);
		UT_ASSERT_FALSE(IS_ENUM<unsigned long>::value);
		UT_ASSERT_FALSE(IS_ENUM<unsigned long long>::value);
	}

	void testWithEnumTypes() {
		UT_ASSERT_TRUE(IS_ENUM<NamedEnum>::value);
	}

	void testWithAnonymousEnum() {
		UT_ASSERT_TRUE(IS_ENUM<AnonymousEnum>::value);
	}
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_TEMPLATE_IS_ENUM_H_INCLUDED */
