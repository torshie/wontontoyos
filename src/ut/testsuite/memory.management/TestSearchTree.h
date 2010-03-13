#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/SearchTree.h"
#include "mm/StackBasedAllocator.h"
#include <cxx/BUG.h>

namespace kernel {

#define IS_RED_BLACK_TREE(rootKey, blackHeight) \
	UT_ASSERT_EQUAL(tree->root->parent, 0); \
	UT_ASSERT_TRUE(Node::isBlack(tree->root)); \
	UT_ASSERT_EQUAL(tree->root->key, rootKey); \
	UT_ASSERT_EQUAL(getBlackHeight(tree->root), blackHeight);

class TestSearchTree : public TestCase {
	typedef SearchTree<int, int>::Allocator Allocator;
	typedef SearchTree<int, int>::Node Node;

	char allocatorSite[sizeof(Allocator)];
	Allocator* allocator;
	char pool[1024];

	char treeSite[sizeof(SearchTree<int, int>)];
	SearchTree<int, int>* tree;

	static int getBlackHeight(Node* node) {
		return SearchTree<int, int>::getBlackHeight(node);
	}

public:
	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		allocator = new (allocatorSite)Allocator();
		allocator->addPool(pool, sizeof(pool));

		tree = new (treeSite) SearchTree<int, int>(*allocator);
	}

	void tearDown() {
		tree->~SearchTree();
		allocator->~Allocator();
	}

	void testEmptyTree() {
		UT_ASSERT_EQUAL(tree->root, 0);
		UT_ASSERT_EQUAL(getBlackHeight(tree->root), 0);
	}

	void testInsertOneNode() {
		tree->insert(1, 1);

		IS_RED_BLACK_TREE(1, 1);
	}

	void testInsertLeftChild() {
		tree->insert(2, 2);
		tree->insert(1, 1);

		IS_RED_BLACK_TREE(2, 1);
	}

	void testInesrtRightChild() {
		tree->insert(2, 2);
		tree->insert(3, 3);

		IS_RED_BLACK_TREE(2, 1);
	}

	void testLeftRotateRoot() {
		Node* root = tree->insert(1, 1);
		tree->insert(2, 2);
		tree->leftRotate(root);

		UT_ASSERT_EQUAL(tree->root->key, 2);
		UT_ASSERT_EQUAL(tree->root->data, 2);
		UT_ASSERT_EQUAL(tree->root->parent, 0);
		UT_ASSERT_EQUAL(tree->root->right, 0);
		UT_ASSERT_EQUAL(tree->root->left->key, 1);
		UT_ASSERT_EQUAL(tree->root->left->data, 1);
		UT_ASSERT_EQUAL(tree->root->left->left, 0);
		UT_ASSERT_EQUAL(tree->root->left->right, 0);
		UT_ASSERT_EQUAL(tree->root->left->parent, tree->root);
	}

	void testRightRotateRoot() {
		Node* root = tree->insert(3, 3);
		tree->insert(2, 2);
		tree->rightRotate(root);

		UT_ASSERT_EQUAL(tree->root->key, 2);
		UT_ASSERT_EQUAL(tree->root->data, 2);
		UT_ASSERT_EQUAL(tree->root->parent, 0);
		UT_ASSERT_EQUAL(tree->root->left, 0);
		UT_ASSERT_EQUAL(tree->root->right->key, 3);
		UT_ASSERT_EQUAL(tree->root->right->data, 3);
		UT_ASSERT_EQUAL(tree->root->right->left, 0);
		UT_ASSERT_EQUAL(tree->root->right->right, 0);
		UT_ASSERT_EQUAL(tree->root->right->parent, tree->root);
	}

	void testInsertLeftAndRightChildren() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);

		IS_RED_BLACK_TREE(2, 1);
	}

	void testInsertFixUp_LeftLeftUncleRed() {
		tree->insert(3, 3);
		tree->insert(2, 2);
		tree->insert(4, 4);
		tree->insert(1, 1);

		IS_RED_BLACK_TREE(3, 2);
	}

	void testInsertFixUp_LeftRightUncleRed() {
		tree->insert(3, 3);
		tree->insert(1, 1);
		tree->insert(4, 4);
		tree->insert(2, 2);

		IS_RED_BLACK_TREE(3, 2);
	}

	void testInertFixUp_RightRightUncleRed() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->insert(4, 4);

		IS_RED_BLACK_TREE(2, 2);
	}

	void testInsertFixUp_RightLeftUncleRed() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(4, 4);
		tree->insert(3, 3);

		IS_RED_BLACK_TREE(2, 2);
	}

	void testInsertFixUp_LeftLeftUncleBlack() {
		tree->insert(3, 3);
		tree->insert(2, 2);
		tree->insert(1, 1);

		IS_RED_BLACK_TREE(2, 1);
	}


	void testInsertFixUp_LeftRightUncleBlack() {
		tree->insert(3, 3);
		tree->insert(1, 1);
		tree->insert(2, 2);

		IS_RED_BLACK_TREE(2, 1);
	}

	void testInsertFixUp_RightRightUncleBlack() {
		tree->insert(1, 1);
		tree->insert(2, 2);
		tree->insert(3, 3);

		IS_RED_BLACK_TREE(2, 1);
	}

	void testInsertFixUp_RightLeftUncleBlack() {
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->insert(2, 2);

		IS_RED_BLACK_TREE(2, 1);
	}

	void testInsertSequentialFourNodes() {
		for (int i = 0; i < 4; ++i) {
			tree->insert(i, i);
		}

		IS_RED_BLACK_TREE(1, 2);
	}

	void testInsertSequentialFiveNodes() {
		for (int i = 0; i < 5; ++i) {
			tree->insert(i, i);
		}

		IS_RED_BLACK_TREE(1, 2);
	}

	void testInsertSequentialSixNodes() {
		for (int i = 0; i < 6; ++i) {
			tree->insert(i, i);
		}

		IS_RED_BLACK_TREE(1, 2);
	}

	void testInsertSequentialSevenNodes() {
		for (int i = 0; i < 7; ++i) {
			tree->insert(i, i);
		}

		IS_RED_BLACK_TREE(1, 2);
	}

	void testInsertSequentialEightNodes() {
		for (int i = 0; i < 8; ++i) {
			tree->insert(i, i);
		}

		IS_RED_BLACK_TREE(3, 2);
	}

	void testGetSuccessor() {
		tree->insert(3, 3);
		tree->insert(1, 1);
		tree->insert(4, 4);
		tree->insert(2, 2);

		IS_RED_BLACK_TREE(3, 2);
		UT_ASSERT_EQUAL((SearchTree<int, int>::getSuccessor(tree->root)), tree->root->right);
		UT_ASSERT_EQUAL((SearchTree<int, int>::getSuccessor(tree->root->left->right)),
				tree->root);
		UT_ASSERT_EQUAL((SearchTree<int, int>::getSuccessor(tree->root->right)), 0);
	}

	void testRemoveSingleNode() {
		tree->insert(1, 1);
		tree->remove(tree->root);

		UT_ASSERT_EQUAL(tree->root, 0);
	}

	void testTwoNodeTree_RemoveRoot_1() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->remove(tree->root);
		IS_RED_BLACK_TREE(1, 1);
	}

	void testTwoNodeTree_RemoveRoot_2() {
		tree->insert(2, 2);
		tree->insert(3, 3);
		tree->remove(tree->root);
		IS_RED_BLACK_TREE(3, 1);
	}

	void testTwoNodeTree_RemoveLeftChild() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->remove(tree->root->left);
		IS_RED_BLACK_TREE(2, 1);
	}

	void testRemovedNodeIsLeftChildAndOnlyHasLeftChild() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->insert(0, 0);
		tree->remove(tree->root->left);
		IS_RED_BLACK_TREE(2, 2);
	}

	void testRemovedNodeIsLeftChildAndOnlyHasRightChild() {
		tree->insert(2, 2);
		tree->insert(0, 0);
		tree->insert(3, 3);
		tree->insert(1, 1);
		tree->remove(tree->root->left);
		IS_RED_BLACK_TREE(2, 2);
	}

	void testRemovedNodeIsRightChildAndOnlyHasLeftChild() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(4, 4);
		tree->insert(3, 3);
		tree->remove(tree->root->right);
		IS_RED_BLACK_TREE(2, 2);
	}

	void testRemovedNodeIsRightChildAndOnlyHasRightChild() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->insert(4, 4);
		tree->remove(tree->root->right);
		IS_RED_BLACK_TREE(2, 2);
	}

	void testRemoveRootOfThreeNodeTree() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->remove(tree->root);
		IS_RED_BLACK_TREE(3, 1);
	}

	void testFixUpRemoveLeft_1() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->insert(4, 4);
		tree->remove(tree->root->right->right);
		IS_RED_BLACK_TREE(2, 2);
	}

	void testFixUpRemoveLeft_2() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(4, 4);
		tree->insert(3, 3);
		tree->remove(tree->root->right->left);
		IS_RED_BLACK_TREE(2, 2);
	}

	void testFixUpRemoveRight_1() {
		tree->insert(3, 3);
		tree->insert(4, 4);
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->remove(tree->root->left->left);
		IS_RED_BLACK_TREE(3, 2);
	}

	void testFixUpRemoveRight_2() {
		tree->insert(3, 3);
		tree->insert(4, 4);
		tree->insert(1, 1);
		tree->insert(2, 2);
		tree->remove(tree->root->left->right);
		IS_RED_BLACK_TREE(3, 2);
	}

	void testRemoveRootOfThreeBlack() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->root->left->red = false;
		tree->root->right->red = false;

		tree->remove(tree->root);
		IS_RED_BLACK_TREE(3, 1);
	}

	void testRemoveLeftOfTreeBlack() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->root->left->red = false;
		tree->root->right->red = false;

		tree->remove(tree->root->left);
		IS_RED_BLACK_TREE(2, 1);
	}

	void testRemoveRightOfTreeBlack() {
		tree->insert(2, 2);
		tree->insert(1, 1);
		tree->insert(3, 3);
		tree->root->left->red = false;
		tree->root->right->red = false;

		tree->remove(tree->root->right);
		IS_RED_BLACK_TREE(2, 1);
	}
};

} // namespace kernel

#endif // KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED
