#ifndef KERNEL_UT_FRAMEWORK_TEST_CASE_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_CASE_H_INCLUDED

namespace kernel {

class TestSuite;

class TestCase {
public:
	typedef void (TestCase::*TestPoint)(void);
public:
	virtual ~TestCase() {}
	virtual void setUp() {}
	virtual void tearDown() {}

	/**
	 * Get a test point.
	 *
	 * Derived test cases should implement this method, but the implementations are generated by
	 * a script
	 *
	 * @return If there is no more test point return false, otherwise return true.
	 */
	virtual bool getTestPoint(TestPoint& point, const char*& name) = 0;
};

} // namespace kernel

#endif // KERNEL_UT_FRAMEWORK_TEST_CASE_H_INCLUDED
