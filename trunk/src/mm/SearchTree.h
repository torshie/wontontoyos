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
	typedef BinaryTreeNode<Key, Data> Node;

	explicit SearchTree(Allocator& alloc) : root(0), allocator(alloc) {}

	~SearchTree() {
		Node::releaseTree(root, allocator);
	}

	Node* insert(const Key& key, const Data& data) {
		void* buffer = allocator.allocate(sizeof(Node));
		Node* node = new (buffer) Node(key, data);

		if (root != 0) {
			Node* cursor = root;
			while (node->parent == 0) {
				if (key < cursor->key) {
					if (cursor->left != 0) {
						cursor = cursor->left;
					} else {
						cursor->left = node;
						node->parent = cursor;
					}
				} else {
					if (cursor->right != 0) {
						cursor = cursor->right;
					} else {
						cursor->right = node;
						node->parent = cursor;
					}
				}
			}
		} else {
			root = node;
		}

		return node;
	}

	void remove(Node* node);

	Node* search(const Key& key) {
		Node* cursor = root;
		while (cursor != 0 && cursor->key != key) {
			if (key < cursor->key) {
				cursor = cursor->left;
			} else {
				cursor = cursor->right;
			}
		}

		if (cursor != 0) {
			return cursor;
		} else {
			return 0;
		}
	}

private:
	Node* root;
	Allocator& allocator;
};

} // namespace kernel

#endif // KERNEL_MM_SEARCH_TREE_H_INCLUDED
