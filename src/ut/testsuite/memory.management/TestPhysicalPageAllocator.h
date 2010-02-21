#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_PHYSICAL_PAGE_ALLOCATOR_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/PhysicalPageAllocator.h"
#include "arch/X64Constant.h"

namespace kernel {

class TestPhysicalPageAllocator : public TestCase {
public:
	bool getTestPoint(TestPoint&, const char*&);

	void testAllocate() {
		PhysicalPageAllocator& allocator
				= getSingleInstance<PhysicalPageAllocator>();
		Address first = allocator.allocate(PAGE_SIZE);
		Address second = allocator.allocate(PAGE_SIZE);
		Address third = allocator.allocate(PAGE_SIZE);
		UT_ASSERT_EQUAL(first + PAGE_SIZE, second);
		UT_ASSERT_EQUAL(second + PAGE_SIZE, third);
	}
};

} /* namespace kernel */

#endif
