#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED

#include "mm/MaxHeap.h"
#include "ut/framework/UnitTesting.h"
#include <cxx/new.h>

namespace kernel {

class TestMaxHeap : public TestCase {
	class Extender {
	public:
		void extend(void*, Size) {}
	};

	char buffer[sizeof(MaxHeap<int, int, Extender>)];
	char memory[4096];
	MaxHeap<int, int, Extender>* heap;

	Extender extender;
public:
	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		heap = new (buffer)MaxHeap<int, int, Extender>(memory, sizeof(memory), extender);
	}

	void tearDown() {
		heap->~MaxHeap();
	}

	void testEmptyMaxHeap() {
		UT_ASSERT_EQUAL(heap->nodeCount, 0);
		UT_ASSERT_EQUAL(heap->bufferSize, sizeof(memory));
		UT_ASSERT_EQUAL(heap->base, &memory);
	}

	void testInsertOneNode() {
		heap->insert(1, 1);

		UT_ASSERT_EQUAL(heap->nodeCount, 1);
		UT_ASSERT_EQUAL(heap->base[0].key, 1);
		UT_ASSERT_EQUAL(heap->base[0].data, 1);
	}

	void testInsertSecondNodeSmallerThanFirst() {
		heap->insert(2, 2);
		heap->insert(1, 1);

		UT_ASSERT_EQUAL(heap->nodeCount, 2);
		UT_ASSERT_EQUAL(heap->base[0].key, 2);
		UT_ASSERT_EQUAL(heap->base[1].key, 1);
	}

	void testInsertSecondNodeLargerThanFirst() {
		heap->insert(1, 1);
		heap->insert(2, 2);

		UT_ASSERT_EQUAL(heap->nodeCount, 2);
		UT_ASSERT_EQUAL(heap->base[0].key, 2);
		UT_ASSERT_EQUAL(heap->base[1].key, 1);
	}

	void testInsertThirdNodeLargerThanRoot() {
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(3, 3);

		UT_ASSERT_EQUAL(heap->nodeCount, 3);
		UT_ASSERT_EQUAL(heap->base[0].key, 3);
		UT_ASSERT_EQUAL(heap->base[1].key, 1);
		UT_ASSERT_EQUAL(heap->base[2].key, 2);
	}

	void testCompleteInsert() {
		int input[] = {2, 1, 4, 3, 3, 6};
		int result[] = {6, 3, 4, 1, 3, 2};

		for (Size i = 0; i < sizeof(input) / sizeof(int); ++i) {
			heap->insert(input[i], input[i]);
		}
		UT_ASSERT_EQUAL(heap->nodeCount, 6);
		for (Size i = 0; i < sizeof(result) / sizeof(int); ++i) {
			UT_ASSERT_EQUAL(heap->base[i].key, result[i]);
		}
	}

	void testRemoveSingleNode() {
		heap->insert(1, 1);
		heap->remove(0);

		UT_ASSERT_EQUAL(heap->nodeCount, 0);
	}

	void testRemoveRootOfTwoNodeHeap() {
		heap->insert(1, 1);
		heap->insert(2, 2);

		heap->remove(0);

		UT_ASSERT_EQUAL(heap->nodeCount, 1);
		UT_ASSERT_EQUAL(heap->base[0].key, 1);
		UT_ASSERT_EQUAL(heap->base[0].data, 1);
	}

	void testRemoveRootOfThreeNodeHeap() {
		heap->insert(3, 3);
		heap->insert(1, 1);
		heap->insert(2, 2);

		heap->remove(0);

		UT_ASSERT_EQUAL(heap->nodeCount, 2);
		UT_ASSERT_EQUAL(heap->base[0].key, 2);
		UT_ASSERT_EQUAL(heap->base[1].key, 1);
	}

	void testSinkAfterRemove() {
		int input[] = {4, 2, 3, 1, 1};
		int result[] = {3, 2, 1, 1};

		for (Size i = 0; i < sizeof(input) / sizeof(int); ++i) {
			heap->insert(input[i], input[i]);
		}
		heap->remove(0);
		for (Size i = 0; i < sizeof(result) / sizeof(int); ++i) {
			UT_ASSERT_EQUAL(heap->base[i].key, result[i]);
		}
	}

	void testDecreaseLeaf() {
		heap->insert(3, 3);
		heap->insert(2, 2);

		heap->decrease(1, 2);

		UT_ASSERT_EQUAL(heap->base[0].key, 3);
		UT_ASSERT_EQUAL(heap->base[1].key, 0);
		UT_ASSERT_EQUAL(heap->base[1].data, 2);
	}

	void testDecreaseRoot() {
		heap->insert(3, 3);
		heap->insert(2, 2);

		heap->decrease(0, 2);

		UT_ASSERT_EQUAL(heap->base[0].key, 2);
		UT_ASSERT_EQUAL(heap->base[1].key, 1);
		UT_ASSERT_EQUAL(heap->base[1].data, 3);
	}

	void testIncreaseRoot() {
		heap->insert(2, 2);
		heap->insert(1, 1);

		heap->increase(0, 2);

		UT_ASSERT_EQUAL(heap->base[0].key, 4);
		UT_ASSERT_EQUAL(heap->base[0].data, 2);
		UT_ASSERT_EQUAL(heap->base[1].key, 1);
	}

	void testIncreaseLeaf() {
		heap->insert(2, 2);
		heap->insert(1, 1);

		heap->increase(1, 2);

		UT_ASSERT_EQUAL(heap->base[0].key, 3);
		UT_ASSERT_EQUAL(heap->base[0].data, 1);
		UT_ASSERT_EQUAL(heap->base[1].key, 2);
	}

	// XXX Test behavior when heap is full.
};

} // namespace kernel

#endif // KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED
