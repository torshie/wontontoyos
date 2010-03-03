#ifndef KERNEL_MM_SEARCH_TREE_H_INCLUDED
#define KERNEL_MM_SEARCH_TREE_H_INCLUDED

#include "StackBasedAllocator.h"
#include "BinaryTreeNode.h"

namespace kernel {

// XXX Implement a red-black tree instead of a simple unbalanced binary search tree
// XXX Make the tree implementation thread-safe
template<typename Key, typename Data,
		typename AllocatorParameter = StackBasedAllocator<sizeof(BinaryTreeNode<Key, Data>)> >
class SearchTree {
	friend class TestSearchTree;
public:
	typedef AllocatorParameter Allocator;

	explicit SearchTree(Allocator& alloc) : root(0), allocator(alloc) {}
	~SearchTree();

	void insert(const Key& key, const Data& data) {
		void* buffer = allocator.allocate(sizeof(BinaryTreeNode<Key, Data>));
		BinaryTreeNode<Key, Data>* node = new (buffer)BinaryTreeNode<Key, Data>(key, data);
		BinaryTreeNode<Key, Data>** cursor = &root;
		while (*cursor != 0) {
			node->parent = *cursor;
			if (key < (*cursor)->key) {
				cursor = &((*cursor)->left);
			} else {
				cursor = &((*cursor)->right);
			}
		}
		*cursor = node;
	}

	void remove(BinaryTreeNode<Key, Data>* node) {
		if (node->right == 0) {
			node->left->parent = node->parent;

			if (isLeftChild(node)) {
				node->parent->left = node->left;
			} else if (isRightChild(node)) {
				node->parent->right = node->left;
			} else {
				// XXX Code here
			}
		} else {
			// XXX Code here
		}
	}

	void remove(const Key& key);

	Data* search(const Key& key) {
		BinaryTreeNode<Key, Data>* cursor = root;
		while (cursor != 0 && cursor->key != key) {
			if (key < cursor->key) {
				cursor = cursor->left;
			} else {
				cursor = cursor->right;
			}
		}

		if (cursor != 0) {
			return (cursor->data);
		} else {
			return 0;
		}
	}

private:
	BinaryTreeNode<Key, Data>* root;
	Allocator& allocator;

	bool isLeftChild(BinaryTreeNode<Key, Data>* node) {
		if (node == 0 || node == root) {
			return false;
		} else {
			return node->parent->left == node;
		}
	}

	bool isRightChild(BinaryTreeNode<Key, Data>* node) {
		if (node == 0 || node == root) {
			return false;
		} else {
			return node->parent->right == node;
		}
	}
};

} // namespace kernel

#endif // KERNEL_MM_SEARCH_TREE_H_INCLUDED
