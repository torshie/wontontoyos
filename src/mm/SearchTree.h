#ifndef KERNEL_MM_SEARCH_TREE_H_INCLUDED
#define KERNEL_MM_SEARCH_TREE_H_INCLUDED

#include "StackBasedAllocator.h"
#include "BinaryTreeNode.h"
#include <cxx/BUG.h>

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

	~SearchTree() {
		if (root == 0) {
			return;
		}

		BinaryTreeNode<Key, Data>* node = root;
		while (true) {
			while (node->left != 0 || node->right != 0) {
				if (node->left != 0) {
					node = node->left;
				} else {
					node = node->right;
				}
			}

			BinaryTreeNode<Key, Data>** tmp = 0;
			if (node->isLeftChild()) {
				tmp = &(node->parent->left);
			} else if (node->isRightChild()) {
				tmp = &(node->parent->right);
			}

			if (node != root) {
				node = node->parent;
				(*tmp)->~BinaryTreeNode();
				allocator.release(*tmp);
				*tmp = 0;
			} else {
				node->~BinaryTreeNode();
				allocator.release(node);
				return;
			}
		}
	}

	void insert(const Key& key, const Data& data) {
		void* buffer = allocator.allocate(sizeof(BinaryTreeNode<Key, Data>));
		BinaryTreeNode<Key, Data>* node = new (buffer) BinaryTreeNode<Key, Data>(key, data);
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

	void remove(BinaryTreeNode<Key, Data>* node);
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
};

} // namespace kernel

#endif // KERNEL_MM_SEARCH_TREE_H_INCLUDED
