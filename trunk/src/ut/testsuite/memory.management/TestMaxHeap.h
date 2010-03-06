#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED

#include "mm/MaxHeap.h"
#include "ut/framework/UnitTesting.h"
#include <cxx/new.h>

namespace kernel {

class TestMaxHeap : public TestCase {
	char buffer[sizeof(MaxHeap<int, int>)];
	MaxHeap<int, int>* heap;

	char pool[4096];
	MaxHeap<int, int>::Allocator allocator;
public:
	// XXX allocator should report error when being destructed
	TestMaxHeap() {
		allocator.addPool(pool, sizeof(pool));
	}

	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		heap = new (buffer) MaxHeap<int, int>(allocator);
	}

	void tearDown() {
		heap->~MaxHeap();
	}

	void testGetParentNodeOfRoot() {
		BinaryTreeNode<int, int>* parent = heap->getParentNode(1);
		UT_ASSERT_EQUAL(parent, 0);
	}

	void testEmptyMaxHeap() {
		UT_ASSERT_EQUAL(heap->nodeCount, 0);
		UT_ASSERT_EQUAL(heap->root, 0);
	}

	void testInsertOneNode() {
		heap->insert(1, 1);

		UT_ASSERT_EQUAL(heap->nodeCount, 1);
		UT_ASSERT_EQUAL(heap->root->key, 1);
		UT_ASSERT_EQUAL(heap->root->data, 1);
	}

	void testInsertSecondNodeSmallerThanFirst() {
		heap->insert(2, 2);
		heap->insert(1, 1);

		UT_ASSERT_EQUAL(heap->nodeCount, 2);
		UT_ASSERT_EQUAL(heap->root->key, 2);
		UT_ASSERT_EQUAL(heap->root->left->key, 1);
	}

	void testInsertTwoNodesSmallerThanFirst() {
		heap->insert(3, 3);
		heap->insert(1, 1);
		heap->insert(2, 2);

		UT_ASSERT_EQUAL(heap->nodeCount, 3);

		UT_ASSERT_EQUAL(heap->root->parent, 0);
		UT_ASSERT_EQUAL(heap->root->key, 3);
		UT_ASSERT_EQUAL(heap->root->data, 3);

		UT_ASSERT_EQUAL(heap->root->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->data, 1);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);
		UT_ASSERT_EQUAL(heap->root->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->right, 0);

		UT_ASSERT_EQUAL(heap->root->right->key, 2);
		UT_ASSERT_EQUAL(heap->root->right->data, 2);
		UT_ASSERT_EQUAL(heap->root->right->parent, heap->root);
		UT_ASSERT_EQUAL(heap->root->right->left, 0);
		UT_ASSERT_EQUAL(heap->root->right->right, 0);
	}

	void testInsertSecondNodeLargerThanFirst() {
		heap->insert(1, 1);
		heap->insert(2, 2);

		UT_ASSERT_EQUAL(heap->nodeCount, 2);

		UT_ASSERT_EQUAL(heap->root->key, 2);
		UT_ASSERT_EQUAL(heap->root->data, 2);
		UT_ASSERT_EQUAL(heap->root->right, 0);
		UT_ASSERT_EQUAL(heap->root->parent, 0);

		UT_ASSERT_EQUAL(heap->root->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->data, 1);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);
		UT_ASSERT_EQUAL(heap->root->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->right, 0);
	}

	void testSwapRootAndLeftChild() {
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->swap(heap->root, heap->root->left);

		UT_ASSERT_EQUAL(heap->root->key, 1);
		UT_ASSERT_EQUAL(heap->root->data, 1);
		UT_ASSERT_EQUAL(heap->root->right, 0);
		UT_ASSERT_EQUAL(heap->root->parent, 0);

		UT_ASSERT_EQUAL(heap->root->left->key, 2);
		UT_ASSERT_EQUAL(heap->root->left->data, 2);
		UT_ASSERT_EQUAL(heap->root->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->right, 0);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);
	}

	void testSwapRootAndRightChild() {
		heap->insert(3, 3);
		heap->insert(1, 1);
		heap->insert(2, 2);
		heap->swap(heap->root, heap->root->right);

		UT_ASSERT_EQUAL(heap->root->key, 2);
		UT_ASSERT_EQUAL(heap->root->data, 2);
		UT_ASSERT_EQUAL(heap->root->parent, 0);

		UT_ASSERT_EQUAL(heap->root->right->key, 3);
		UT_ASSERT_EQUAL(heap->root->right->data, 3);
		UT_ASSERT_EQUAL(heap->root->right->parent, heap->root);
		UT_ASSERT_EQUAL(heap->root->right->left, 0);
		UT_ASSERT_EQUAL(heap->root->right->right, 0);
	}

	void testSwapNotDirectlyLinkedNodes() {
		heap->insert(8, 8);
		heap->insert(7, 7);
		heap->insert(6, 6);

		heap->insert(1, 1);
		heap->insert(2, 2);
		heap->insert(3, 3);
		heap->insert(4, 4);

		heap->swap(heap->root->left, heap->root->right);

		UT_ASSERT_EQUAL(heap->root->parent, 0);
		UT_ASSERT_EQUAL(heap->root->key, 8);
		UT_ASSERT_EQUAL(heap->root->data, 8);

		UT_ASSERT_EQUAL(heap->root->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->data, 1);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);
		UT_ASSERT_EQUAL(heap->root->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->right, 0);

		UT_ASSERT_EQUAL(heap->root->right->key, 2);
		UT_ASSERT_EQUAL(heap->root->right->data, 2);
		UT_ASSERT_EQUAL(heap->root->right->parent, heap->root);
		UT_ASSERT_EQUAL(heap->root->right->left, 0);
		UT_ASSERT_EQUAL(heap->root->right->right, 0);
	}

	void testInsertThirdNodeLargerThanRoot() {
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(3, 3);

		UT_ASSERT_EQUAL(heap->nodeCount, 3);
		UT_ASSERT_EQUAL(heap->root->key, 3);
		UT_ASSERT_EQUAL(heap->root->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->right->key, 2);
	}

	void testInsertFourNodesSwapParentAndLeftChild() {
		heap->insert(4, 4);
		heap->insert(1, 1);
		heap->insert(2, 2);
		heap->insert(3, 3);

		UT_ASSERT_EQUAL(heap->root->key, 4);

		UT_ASSERT_EQUAL(heap->root->left->key, 3);
		UT_ASSERT_EQUAL(heap->root->left->data, 3);
		UT_ASSERT_EQUAL(heap->root->left->right, 0);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);

		UT_ASSERT_EQUAL(heap->root->right->key, 2);

		UT_ASSERT_EQUAL(heap->root->left->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->left->data, 1);
		UT_ASSERT_EQUAL(heap->root->left->left->parent, heap->root->left);
		UT_ASSERT_EQUAL(heap->root->left->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->left->right, 0);
	}

	void testInsertFiveNodesWithoutSwap() {
		heap->insert(4, 4);
		heap->insert(3, 3);
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(0, 0);

		UT_ASSERT_EQUAL(heap->root->key, 4);
		UT_ASSERT_EQUAL(heap->root->left->key, 3);
		UT_ASSERT_EQUAL(heap->root->right->key, 2);

		UT_ASSERT_EQUAL(heap->root->left->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->left->data, 1);
		UT_ASSERT_EQUAL(heap->root->left->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->left->right, 0);
		UT_ASSERT_EQUAL(heap->root->left->left->parent, heap->root->left);

		UT_ASSERT_EQUAL(heap->root->left->right->key, 0);
		UT_ASSERT_EQUAL(heap->root->left->right->data, 0);
		UT_ASSERT_EQUAL(heap->root->left->right->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->right->right, 0);
		UT_ASSERT_EQUAL(heap->root->left->right->parent, heap->root->left);
	}

	void testComplexInsert() {
//		int input[] = {2, 1, 4, 3, 3, 6};
//
//		for (Size i = 0; i < sizeof(input) / sizeof(int); ++i) {
//			heap->insert(input[i], input[i]);
//		}
//
//		UT_ASSERT_EQUAL(heap->nodeCount, 6);
//
//		UT_ASSERT_EQUAL(heap->root->key, 6);
//		UT_ASSERT_EQUAL(heap->root->left->key, 3);
//		UT_ASSERT_EQUAL(heap->root->right->key, 4);
//		UT_ASSERT_EQUAL(heap->root->left->left->key, 1);
//		UT_ASSERT_EQUAL(heap->root->left->right->key, 3);
//		UT_ASSERT_EQUAL(heap->root->right->left->key, 2);
	}
//
//	void testRemoveSingleNode() {
//		heap->insert(1, 1);
//		heap->remove(0);
//
//		UT_ASSERT_EQUAL(heap->nodeCount, 0);
//	}
//
//	void testRemoveRootOfTwoNodeHeap() {
//		heap->insert(1, 1);
//		heap->insert(2, 2);
//
//		heap->remove(0);
//
//		UT_ASSERT_EQUAL(heap->nodeCount, 1);
//		UT_ASSERT_EQUAL(heap->base[0].key, 1);
//		UT_ASSERT_EQUAL(heap->base[0].data, 1);
//	}
//
//	void testRemoveRootOfThreeNodeHeap() {
//		heap->insert(3, 3);
//		heap->insert(1, 1);
//		heap->insert(2, 2);
//
//		heap->remove(0);
//
//		UT_ASSERT_EQUAL(heap->nodeCount, 2);
//		UT_ASSERT_EQUAL(heap->base[0].key, 2);
//		UT_ASSERT_EQUAL(heap->base[1].key, 1);
//	}
//
//	void testSinkAfterRemove() {
//		int input[] = {4, 2, 3, 1, 1};
//		int result[] = {3, 2, 1, 1};
//
//		for (Size i = 0; i < sizeof(input) / sizeof(int); ++i) {
//			heap->insert(input[i], input[i]);
//		}
//		heap->remove(0);
//		for (Size i = 0; i < sizeof(result) / sizeof(int); ++i) {
//			UT_ASSERT_EQUAL(heap->base[i].key, result[i]);
//		}
//	}
//
//	void testDecreaseLeaf() {
//		heap->insert(3, 3);
//		heap->insert(2, 2);
//
//		heap->decrease(1, 2);
//
//		UT_ASSERT_EQUAL(heap->base[0].key, 3);
//		UT_ASSERT_EQUAL(heap->base[1].key, 0);
//		UT_ASSERT_EQUAL(heap->base[1].data, 2);
//	}
//
//	void testDecreaseRoot() {
//		heap->insert(3, 3);
//		heap->insert(2, 2);
//
//		heap->decrease(0, 2);
//
//		UT_ASSERT_EQUAL(heap->base[0].key, 2);
//		UT_ASSERT_EQUAL(heap->base[1].key, 1);
//		UT_ASSERT_EQUAL(heap->base[1].data, 3);
//	}
//
//	void testIncreaseRoot() {
//		heap->insert(2, 2);
//		heap->insert(1, 1);
//
//		heap->increase(0, 2);
//
//		UT_ASSERT_EQUAL(heap->base[0].key, 4);
//		UT_ASSERT_EQUAL(heap->base[0].data, 2);
//		UT_ASSERT_EQUAL(heap->base[1].key, 1);
//	}
//
//	void testIncreaseLeaf() {
//		heap->insert(2, 2);
//		heap->insert(1, 1);
//
//		heap->increase(1, 2);
//
//		UT_ASSERT_EQUAL(heap->base[0].key, 3);
//		UT_ASSERT_EQUAL(heap->base[0].data, 1);
//		UT_ASSERT_EQUAL(heap->base[1].key, 2);
//	}
};

} // namespace kernel

#endif // KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED
