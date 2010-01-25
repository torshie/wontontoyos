#ifndef KERNEL_UT_FRAMEWORK_TEST_CASE_H_INCLUDED
#define KERNEL_UT_FRAMEWORK_TEST_CASE_H_INCLUDED

namespace kernel {

class TestSuite;

class TestCase {
protected:
	typedef void (TestCase::*TestPoint)(void);
public:
	virtual ~TestCase() {}
	virtual void setUp() {}
	virtual void tearDown() {}
	virtual bool getTestPoint(TestPoint& point, const char*& name) = 0;
};

} /* namespace kernel */

#endif /* KERNEL_UT_FRAMEWORK_TEST_CASE_H_INCLUDED */
