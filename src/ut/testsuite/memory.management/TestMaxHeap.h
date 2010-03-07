#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED

#include "mm/MaxHeap.h"
#include "ut/framework/UnitTesting.h"
#include <cxx/new.h>

namespace kernel {

class TestMaxHeap : public TestCase {
	typedef MaxHeap<int, int>::Node Node;
	typedef MaxHeap<int, int>::Allocator Allocator;
	char heapSite[sizeof(MaxHeap<int, int>)];
	MaxHeap<int, int>* heap;

	char pool[4096];
	char allocatorSite[sizeof(Allocator)];
	Allocator* allocator;
public:
	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		allocator = new (allocatorSite) Allocator();
		allocator->addPool(pool, sizeof(pool));
		heap = new (heapSite) MaxHeap<int, int>(*allocator);
	}

	void tearDown() {
		heap->~MaxHeap();
		allocator->~Allocator();
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

	void testSwapUnlinkedNodes() {
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

		UT_ASSERT_EQUAL(heap->root->left->key, 6);
		UT_ASSERT_EQUAL(heap->root->left->data, 6);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);

		UT_ASSERT_EQUAL(heap->root->right->key, 7);
		UT_ASSERT_EQUAL(heap->root->right->data, 7);
		UT_ASSERT_EQUAL(heap->root->right->parent, heap->root);

		UT_ASSERT_EQUAL(heap->root->left->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->left->right, 0);
		UT_ASSERT_EQUAL(heap->root->left->left->parent, heap->root->left);

		UT_ASSERT_EQUAL(heap->root->left->right->key, 2);
		UT_ASSERT_EQUAL(heap->root->left->right->left, 0);
		UT_ASSERT_EQUAL(heap->root->left->right->right, 0);
		UT_ASSERT_EQUAL(heap->root->left->right->parent, heap->root->left);

		UT_ASSERT_EQUAL(heap->root->right->left->key, 3);
		UT_ASSERT_EQUAL(heap->root->right->left->left, 0);
		UT_ASSERT_EQUAL(heap->root->right->left->right, 0);
		UT_ASSERT_EQUAL(heap->root->right->left->parent, heap->root->right);

		UT_ASSERT_EQUAL(heap->root->right->right->key, 4);
		UT_ASSERT_EQUAL(heap->root->right->right->left, 0);
		UT_ASSERT_EQUAL(heap->root->right->right->right, 0);
		UT_ASSERT_EQUAL(heap->root->right->right->parent, heap->root->right);
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
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(4, 4);
		heap->insert(3, 3);
		heap->insert(3, 3);
		heap->insert(6, 6);

		UT_ASSERT_EQUAL(heap->nodeCount, 6);

		UT_ASSERT_EQUAL(heap->root->key, 6);
		UT_ASSERT_EQUAL(heap->root->parent, 0);

		UT_ASSERT_EQUAL(heap->root->left->key, 3);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);

		UT_ASSERT_EQUAL(heap->root->right->key, 4);
		UT_ASSERT_EQUAL(heap->root->right->parent, heap->root);

		UT_ASSERT_EQUAL(heap->root->left->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->left->parent, heap->root->left);

		UT_ASSERT_EQUAL(heap->root->left->right->key, 3);
		UT_ASSERT_EQUAL(heap->root->left->right->parent, heap->root->left);

		UT_ASSERT_EQUAL(heap->root->right->left->key, 2);
		UT_ASSERT_EQUAL(heap->root->right->left->parent, heap->root->right);
	}

	void testSinkRootOfTwoNodeHeap() {
		heap->insert(2, 2);
		heap->insert(1, 1);

		heap->root->left->key = 3;
		heap->root->left->data = 3;
		heap->sink(heap->root);

		UT_ASSERT_EQUAL(heap->root->key, 3);
		UT_ASSERT_EQUAL(heap->root->parent, 0);
		UT_ASSERT_EQUAL(heap->root->left->key, 2);
		UT_ASSERT_EQUAL(heap->root->left->parent, heap->root);
	}


	void testRemoveSingleNode() {
		Node* node = heap->insert(1, 1);
		heap->remove(node);

		UT_ASSERT_EQUAL(heap->nodeCount, 0);
		UT_ASSERT_EQUAL(heap->root, 0);
	}

	void testRemoveLeftChild() {
		heap->insert(2, 2);
		Node* left = heap->insert(1, 1);
		heap->remove(left);

		UT_ASSERT_EQUAL(heap->nodeCount, 1);
		UT_ASSERT_EQUAL(heap->root->left, 0);
		UT_ASSERT_EQUAL(heap->root->right, 0);
		UT_ASSERT_EQUAL(heap->root->parent, 0);
		UT_ASSERT_EQUAL(heap->root->key, 2);
		UT_ASSERT_EQUAL(heap->root->data, 2);
	}

	void testRemoveRightChild() {
		heap->insert(3, 3);
		heap->insert(2, 2);
		Node* right = heap->insert(1, 1);
		heap->remove(right);

		UT_ASSERT_EQUAL(heap->nodeCount, 2);
		UT_ASSERT_EQUAL(heap->root->right, 0);
		UT_ASSERT_EQUAL(heap->root->key, 3);
		UT_ASSERT_EQUAL(heap->root->left->key, 2);
	}

	void testRemoveRootOfTwoNodeHeap() {
		Node* root = heap->insert(2, 2);
		heap->insert(1, 1);
		heap->remove(root);

		UT_ASSERT_EQUAL(heap->nodeCount, 1);
		UT_ASSERT_EQUAL(heap->root->key, 1);
		UT_ASSERT_EQUAL(heap->root->data, 1);
		UT_ASSERT_EQUAL(heap->root->left, 0);
		UT_ASSERT_EQUAL(heap->root->parent, 0);
		UT_ASSERT_EQUAL(heap->root->right, 0);
	}

	void testRemoveRootOfThreeNodeHeap() {
		Node* root = heap->insert(3, 3);
		heap->insert(1, 1);
		heap->insert(2, 2);
		heap->remove(root);

		UT_ASSERT_EQUAL(heap->nodeCount, 2);
		UT_ASSERT_EQUAL(heap->root->key, 2);
		UT_ASSERT_EQUAL(heap->root->right, 0);
		UT_ASSERT_EQUAL(heap->root->left->key, 1);
	}

	void testSinkAfterRemove() {
		Node* root = heap->insert(4, 4);
		heap->insert(3, 3);
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(1, 1);
		heap->remove(root);

		UT_ASSERT_EQUAL(heap->nodeCount, 4);
		UT_ASSERT_EQUAL(heap->root->key, 3);
		UT_ASSERT_EQUAL(heap->root->right->key, 2);
		UT_ASSERT_EQUAL(heap->root->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->left->key, 1);
	}

	void testDecreaseRoot() {
		Node* root = heap->insert(3, 3);
		heap->insert(2, 2);

		heap->decrease(root, 2);

		UT_ASSERT_EQUAL(heap->root->key, 2);
		UT_ASSERT_EQUAL(heap->root->left->key, 1);
		UT_ASSERT_EQUAL(heap->root->left->data, 3);
	}


	void testIncreaseLeaf() {
		heap->insert(2, 2);
		Node* leaf = heap->insert(1, 1);

		heap->increase(leaf, 2);

		UT_ASSERT_EQUAL(heap->root->key, 3);
		UT_ASSERT_EQUAL(heap->root->data, 1);
		UT_ASSERT_EQUAL(heap->root->left->data, 2);
		UT_ASSERT_EQUAL(heap->root->left->key, 2);
	}
};

} // namespace kernel

#endif // KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED
