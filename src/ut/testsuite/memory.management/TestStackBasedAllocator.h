#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_STACK_BASED_ALLOCATOR_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_STACK_BASED_ALLOCATOR_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/StackBasedAllocator.h"
#include <generic/type.h>
#include <generic/OFFSET_OF.h>
#include <cxx/BUG.h>

namespace kernel {

class TestStackBasedAllocator : public TestCase {
	char buffer[sizeof(StackBasedAllocator<sizeof(Address)>)];
	StackBasedAllocator<sizeof(Address)>* allocator;

public:
	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		allocator = new (buffer)StackBasedAllocator<sizeof(Address)>();
	}

	void tearDown() {
		allocator->~StackBasedAllocator<sizeof(Address)>();
	}

	void testAddPool() {
		char pool[512];
		allocator->addPool(pool, sizeof(pool));

		UT_ASSERT_EQUAL(allocator->stack.peek(),
				pool + sizeof(pool) - sizeof(SimpleStack<Address>::Node));
	}

	void testAllocateWithoutPool() {
		UT_ASSERT_EQUAL(allocator->allocate(sizeof(Address)), 0);
	}

	void testSingleNodePool() {
		char pool[sizeof(SimpleStack<Address>::Node)];
		allocator->addPool(pool, sizeof(pool));

		void* pointer = allocator->allocate(sizeof(Address));
		UT_ASSERT_EQUAL(pointer, pool + OFFSET_OF(SimpleStack<Address>::Node, load));
		UT_ASSERT_EQUAL(allocator->allocate(sizeof(Address)), 0);
		allocator->release(pointer);
	}

	void testAllocateReleasedNode() {
		char pool[sizeof(SimpleStack<Address>::Node)];
		allocator->addPool(pool, sizeof(pool));

		void* first = allocator->allocate(sizeof(Address));
		allocator->release(first);
		void* second = allocator->allocate(sizeof(Address));
		UT_ASSERT_EQUAL(first, second);
		allocator->release(second);
	}

	void testAddPoolSmallerThanOneNode() {
		char pool[1];
		allocator->addPool(pool, sizeof(pool));

		UT_ASSERT_EQUAL(allocator->allocate(sizeof(Address)), 0);
	}
};

} // namespace kernel

#endif // KERNEL_MEMORY_MANAGEMENT_TEST_STACK_BASED_ALLOCATOR_H_INCLUDED
