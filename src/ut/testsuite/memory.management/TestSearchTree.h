#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/SearchTree.h"
#include "mm/StackBasedAllocator.h"

namespace kernel {

class TestSearchTree : public TestCase {
	typedef typename SearchTree<int, int>::Allocator Allocator;

	char pool[1024];
	Allocator allocator;

	char buffer[sizeof(SearchTree<int, int>)];
	SearchTree<int, int>* tree;

public:
	TestSearchTree() {
		allocator.addPool(pool, sizeof(pool));
	}

	bool getTestPoint(TestPoint&, const char*&);

	void setUp() {
		tree = new (buffer) SearchTree<int, int>(allocator);
	}

	void tearDown() {
		tree->~SearchTree();
	}

	void testEmptyTree() {
		UT_ASSERT_EQUAL(tree->root, 0);
	}

	void testInsertRoot() {
		tree->insert(1, 1);

		UT_ASSERT_UNEQUAL(tree->root, 0);

		UT_ASSERT_EQUAL(tree->root.left, 0);
		UT_ASSERT_EQUAL(tree->root.right, 0);
		UT_ASSERT_EQUAL(tree->root.parent, 0);
		UT_ASSERT_EQUAL(tree->root.key, 1);
		UT_ASSERT_EQUAL(tree->root.data, 1);
	}

	void testInsertLeftChild() {
		tree->insert(2, 2);
		tree->insert(1, 1);

		UT_ASSERT_UNEQUAL(tree->root, 0);
		UT_ASSERT_UNEQUAL(tree->root->left, 0);

		UT_ASSERT_EQUAL(tree->root.key, 2);
		UT_ASSERT_EQUAL(tree->root.data, 2);
		UT_ASSERT_EQUAL(tree->root.right, 0);

		UT_ASSERT_EQUAL(tree->root->left.parent, tree->root);
		UT_ASSERT_EQUAL(tree->root->left.left, 0);
		UT_ASSERT_EQUAL(tree->root->left.right, 0);
		UT_ASSERT_EQUAL(tree->root->left.key, 1);
		UT_ASSERT_EQUAL(tree->root->left.data, 1);
	}

	void testInsertRightChild() {
		tree->insert(1, 1);
		tree->insert(2, 2);

		UT_ASSERT_UNEQUAL(tree->root, 0);
		UT_ASSERT_UNEQUAL(tree->root->right, 0);

		UT_ASSERT_EQUAL(tree->root.key, 1);
		UT_ASSERT_EQUAL(tree->root.data, 1);
		UT_ASSERT_EQUAL(tree->root.left, 0);

		UT_ASSERT_EQUAL(tree->root->right.parent, tree->root);
		UT_ASSERT_EQUAL(tree->root->right.left, 0);
		UT_ASSERT_EQUAL(tree->root->right.right, 0);
		UT_ASSERT_EQUAL(tree->root->right.key, 2);
		UT_ASSERT_EQUAL(tree->root->right.data, 2);
	}

	void testInsertLeftRightChild() {
		tree->insert(3, 3);
		tree->insert(1, 1);
		tree->insert(2, 2);

		UT_ASSERT_UNEQUAL(tree->root, 0);
		UT_ASSERT_UNEQUAL(tree->root->left, 0);
		UT_ASSERT_UNEQUAL(tree->root->left->right, 0);

		UT_ASSERT_EQUAL(tree->root.key, 3);
		UT_ASSERT_EQUAL(tree->root->left.key, 1);
		UT_ASSERT_EQUAL(tree->root->left->right.key, 2);
		UT_ASSERT_EQUAL(tree->root->left->right.data, 2);
		UT_ASSERT_EQUAL(tree->root->left->right.parent, tree->root->left);
	}
};

} // namespace kernel

#endif // KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED
