#include <sexy/IS_ENUM.h>
#include "ut/framework/UnitTesting.h"

namespace kernel {

class TestIS_ENUM : public TestCase {
	enum NamedEnum {};
	typedef enum {} AnonymousEnum;
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testInteger() {
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

	void testEnum() {
		UT_ASSERT_TRUE(IS_ENUM<NamedEnum>::value);
	}

	void testAnonymousEnum() {
		UT_ASSERT_TRUE(IS_ENUM<AnonymousEnum>::value);
	}
};

} /* namespace kernel */
