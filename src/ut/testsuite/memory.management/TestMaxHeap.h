#include "mm/MaxHeap.h"
#include "ut/framework/UnitTesting.h"
#include <cxx/new.h>

#define IS_MAX_HEAP(rootKey, height) \
	UT_ASSERT_EQUAL(heap->root->key, rootKey); \
	UT_ASSERT_EQUAL(heap->getHeapHeight(), height); \
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
		UT_ASSERT_EQUAL(heap->getHeapHeight(), 0);
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
		heap->insert(4, 4);
		Node* left = heap->insert(1, 1);
		heap->insert(3, 3);
		heap->remove(left);

		IS_MAX_HEAP(4, 2);
		UT_ASSERT_EQUAL(heap->root->left->key, 3);
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

		IS_MAX_HEAP(2, 2);
	}

	void testBubbleAfterIncrease() {
		heap->insert(2, 2);
		Node* leaf = heap->insert(1, 1);
		heap->increase(leaf, 2);

		IS_MAX_HEAP(3, 2);
	}
};

} // namespace kernel
