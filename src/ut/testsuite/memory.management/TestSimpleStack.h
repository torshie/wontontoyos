#include "ut/framework/UnitTesting.h"
#include "mm/SimpleStack.h"
#include <cxx/new.h>

namespace kernel {

class TestSimpleStack : public TestCase {
	char buffer[sizeof(SimpleStack<int>)];
	SimpleStack<int>* stack;
public:
	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		stack = new (buffer)SimpleStack<int>();
	}

	void tearDown() {
		stack->~SimpleStack<int>();
	}

	void testPeekEmptyStack() {
		UT_ASSERT_EQUAL(stack->peek(), 0);
	}

	void testPopEmptyStack() {
		UT_ASSERT_EQUAL(stack->pop(), 0);
		UT_ASSERT_EQUAL(stack->pop(), 0);
	}

	void testPushPop() {
		SimpleStack<int>::Node node;
		stack->push(&node);
		UT_ASSERT_EQUAL(stack->peek(), &node);
		SimpleStack<int>::Node* n = stack->pop();
		UT_ASSERT_EQUAL(n, &node);
	}

};

} // namespace kernel
