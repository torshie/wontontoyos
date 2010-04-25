#include "ut/framework/UnitTesting.h"
#include "mm/GenericAllocator.h"

namespace kernel {

class TestGenericAllocator : public TestCase {
	GenericAllocator& allocator;
public:
	TestGenericAllocator() : allocator(getSingleInstance<GenericAllocator>()) {}

	bool getTestPoint(TestPoint&, const char*&);

//	void testAllocateAlignedObject() {
//		U64* data = (U64*)allocator.allocate(sizeof(U64));
//		*data = 0x900d;
//		UT_ASSERT_EQUAL(*data, 0x900d);
//		allocator.release(data);
//	}
//
//	void testAllocateAndRelease() {
//		void* first = allocator.allocate(1);
//		allocator.release(first);
//		void* second = allocator.allocate(1);
//		UT_ASSERT_EQUAL(first, second);
//		allocator.release(second);
//	}
//
//	void testAddressOfSequentialAllocation() {
//		void* first = allocator.allocate(1);
//		void* second = allocator.allocate(2);
//		UT_ASSERT_EQUAL(((char*)second + 8), (char*)first);
//		allocator.release(first);
//		allocator.release(second);
//	}
//
	void testMerge() {
		void* first = allocator.allocate(16);
		void* second = allocator.allocate(24);
		allocator.release(second);
		allocator.release(first);
		void* third = allocator.allocate(16);
		UT_ASSERT_EQUAL(first, third);
		allocator.release(third);
	}
};

} // namespace kernel
