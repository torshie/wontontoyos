#ifndef KERNEL_UTILITIES_TEST_BASENAME_H_INCLUDED
#define KERNEL_UTILITIES_TEST_BASENAME_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include <generic/Utils.h>

namespace kernel {

class TestBasename : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testSimpleRelativePath() {
		UT_ASSERT_EQUAL(Utils::basename("dir/file"), "file");
	}

	void testNakedPath() {
		UT_ASSERT_EQUAL(Utils::basename("file"), "file");
	}

	void testEmptyPath() {
		UT_ASSERT_EQUAL(Utils::basename(""), "");
	}

	void testAbsolutePath() {
		UT_ASSERT_EQUAL(Utils::basename("/file"), "file");
	}

	void testDirectoryPath() {
		UT_ASSERT_EQUAL(Utils::basename("/dir/"), "dir");
	}

	void testNullString() {
		UT_ASSERT_EQUAL(Utils::basename(0), (const char*)0);
	}
};

} /* namespace kernel */

#endif /* KERNEL_UTILITIES_TEST_BASENAME_H_INCLUDED */
