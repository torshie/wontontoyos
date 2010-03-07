#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_MAX_HEAP_H_INCLUDED

#include "mm/MaxHeap.h"
#include "ut/framework/UnitTesting.h"
#include <cxx/new.h>

#define IS_MAX_HEAP(rootKey, height) \
	UT_ASSERT_EQUAL(heap->root->key, rootKey); \
	UT_ASSERT_EQUAL(getHeapHeight(heap->root), height); \
	UT_ASSERT_EQUAL(heap->root->parent, 0);

namespace kernel {

class TestMaxHeap : public TestCase {
	typedef MaxHeap<int, int>::Node Node;
	typedef MaxHeap<int, int>::Allocator Allocator;
	char heapSite[sizeof(MaxHeap<int, int>)];
	MaxHeap<int, int>* heap;

	char pool[4096];
	char allocatorSite[sizeof(Allocator)];
	Allocator* allocator;

	static int getHeapHeight(Node* node) {
		if (node == 0) {
			return 0;
		}

		if (node->left == 0 && node->right != 0) {
			return -1;
		}

		if (node->left != 0) {
			if (node->left->key > node->key) {
				return -1;
			}
			if (node->left->parent != node) {
				return -1;
			}
		}
		if (node->right != 0) {
			if (node->right->key > node->key) {
				return -1;
			}
			if (node->right->parent != node) {
				return -1;
			}
		}

		int leftHeight = getHeapHeight(node->left);
		int rightHeight = getHeapHeight(node->right);
		if (leftHeight == -1 || rightHeight == -1 || leftHeight < rightHeight
				|| leftHeight - rightHeight > 1) {
			return -1;
		}
		return leftHeight + 1;
	}

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
		HeapNode<int, int>* parent = heap->getParentNode(1);
		UT_ASSERT_EQUAL(parent, 0);
	}

	void testEmptyMaxHeap() {
		UT_ASSERT_EQUAL(heap->root, 0);
		UT_ASSERT_EQUAL(getHeapHeight(heap->root), 0);
	}

	void testInsertOneNode() {
		heap->insert(1, 1);

		IS_MAX_HEAP(1, 1);
	}

	void testInsertSecondNodeSmallerThanFirst() {
		heap->insert(2, 2);
		heap->insert(1, 1);

		IS_MAX_HEAP(2, 2);
	}

	void testInsertTwoNodesSmallerThanFirst() {
		heap->insert(3, 3);
		heap->insert(1, 1);
		heap->insert(2, 2);

		IS_MAX_HEAP(3, 2);
	}

	void testInsertSecondNodeLargerThanFirst() {
		heap->insert(1, 1);
		heap->insert(2, 2);

		IS_MAX_HEAP(2, 2);
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

	void testSwapSeparateNodes() {
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

		IS_MAX_HEAP(3, 2);
	}

	void testInsertFourNodesSwapParentAndLeftChild() {
		heap->insert(4, 4);
		heap->insert(1, 1);
		heap->insert(2, 2);
		heap->insert(3, 3);

		UT_ASSERT_EQUAL(heap->root->key, 4);

		IS_MAX_HEAP(4, 3);
	}

	void testInsertFiveNodesWithoutSwap() {
		heap->insert(4, 4);
		heap->insert(3, 3);
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(0, 0);

		IS_MAX_HEAP(4, 3);
	}

	void testComplexInsert() {
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(4, 4);
		heap->insert(3, 3);
		heap->insert(3, 3);
		heap->insert(6, 6);

		IS_MAX_HEAP(6, 3);
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

		IS_MAX_HEAP(2, 1);
	}

	void testRemoveRightChild() {
		heap->insert(3, 3);
		heap->insert(2, 2);
		Node* right = heap->insert(1, 1);
		heap->remove(right);

		IS_MAX_HEAP(3, 2);
	}

	void testRemoveRootOfTwoNodeHeap() {
		Node* root = heap->insert(2, 2);
		heap->insert(1, 1);
		heap->remove(root);

		IS_MAX_HEAP(1, 1);
	}

	void testRemoveRootOfThreeNodeHeap() {
		Node* root = heap->insert(3, 3);
		heap->insert(1, 1);
		heap->insert(2, 2);
		heap->remove(root);

		IS_MAX_HEAP(2, 2);
	}

	void testSinkAfterRemoval() {
		Node* root = heap->insert(4, 4);
		heap->insert(3, 3);
		heap->insert(2, 2);
		heap->insert(1, 1);
		heap->insert(1, 1);
		heap->remove(root);

		IS_MAX_HEAP(3, 3);
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
