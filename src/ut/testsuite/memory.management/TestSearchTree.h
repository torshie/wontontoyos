#ifndef KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED
#define KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED

#include "ut/framework/UnitTesting.h"
#include "mm/SearchTree.h"
#include "mm/StackBasedAllocator.h"

namespace kernel {

class TestSearchTree : public TestCase {
	typedef SearchTree<int, int> Tree;
	typedef Tree::Node Node;
	typedef Tree::Allocator Allocator;

	char pool[1024];
	Allocator allocator;
public:
	TestSearchTree() {
		allocator.addPool(pool, sizeof(pool));
	}

	bool getTestPoint(TestPoint&, const char*&);

	void testCreateEmptyTree() {
		char buffer[sizeof(Tree)];
		Tree* tree = new (buffer)Tree(allocator);
		UT_ASSERT_EQUAL(tree->root, 0);
	}
};

} // namespace kernel

#endif // KERNEL_MEMORY_MANAGEMENT_TEST_SEARCH_TREE_H_INCLUDED
