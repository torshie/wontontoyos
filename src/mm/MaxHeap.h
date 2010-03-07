#ifndef KERNEL_MM_MAX_HEAP_H_INCLUDED
#define KERNEL_MM_MAX_HEAP_H_INCLUDED

#include "BinaryTreeNode.h"
#include "StackBasedAllocator.h"
#include <cxx/BUG.h>

namespace kernel {

template<typename Key, typename Data,
		typename AllocatorParameter =
				StackBasedAllocator<sizeof(BinaryTreeNode<Key, Data>)> >
class MaxHeap {
	friend class TestMaxHeap;
public:
	typedef BinaryTreeNode<Key, Data> Node;
	typedef AllocatorParameter Allocator;

	MaxHeap(Allocator& alloc) : root(0), nodeCount(0), allocator(alloc) {}

	~MaxHeap() {
		BinaryTreeNode<Key, Data>::releaseTree(root, allocator);
	}

	Node* insert(const Key& key, const Data& data) {
		void* buffer = allocator.allocate(sizeof(Node));
		BinaryTreeNode<Key, Data>* node = new (buffer) Node(key, data);

		++nodeCount;
		Node* parent = getParentNode(nodeCount);
		if (parent != 0) {
			if (parent->left == 0) {
				parent->left = node;
			} else {
				parent->right = node;
			}
			node->parent = parent;
			bubble(node);
		} else {
			root = node;
		}

		return node;
	}

	void remove(Node* node) {
		--nodeCount;

		if (nodeCount == 0) {
			if (node == root) {
				allocator.release(root);
				root = 0;
			} else {
				BUG("node != root");
			}
			return;
		}

		Node* parent = getParentNode(nodeCount + 1);
		Node* last;
		bool leftChild = (parent->right == 0);
		if (leftChild) {
			last = parent->left;
		} else {
			last = parent->right;
		}

		swap(last, node);
		if (leftChild) {
			node->parent->left = 0;
		} else {
			node->parent->right = 0;
		}
		allocator.release(node);

		sink(last);
	}

	void decrease(Node* node, const Key& key) {
		node->key -= key;
		sink(node);
	}

	void increase(Node* node, const Key& key) {
		node->key += key;
		bubble(node);
	}

private:
	Node* root;
	Size nodeCount;
	Allocator& allocator;

	/**
	 * Get a pointer to a node's parent.
	 * The caller should make sure than the given node's parent does actually exist. But
	 * the given node may not exist.
	 *
	 * @param index The index of the given node
	 *
	 * @return A pointer to the given node's parent.
	 */
	Node* getParentNode(Size index) {
		Size parent = index / 2;
		Size mask = 0x8000000000000000LL;
		for (; (mask & parent) == 0 && mask > 0; mask >>= 1)
			;
		if (mask == 0) {
			return 0;
		}

		Node* cursor = root;
		mask >>= 1;
		for (; mask > 0; mask >>= 1) {
			Size value = (mask & parent);
			if (value != 0) {
				cursor = cursor->right;
			} else {
				cursor = cursor->left;
			}
		}

		return cursor;
	}

	void bubble(Node* node) {
		if ((node == root) || (node->key <= node->parent->key)) {
			return;
		}

		Node* parent = node->parent;
		swap(node, parent);
		bubble(node);
	}

	void sink(Node* node) {
		Node* largest = node;
		if (node->left != 0 && largest->key < node->left->key) {
			largest = node->left;
		}
		if (node->right != 0 && largest->key < node->right->key) {
			largest = node->right;
		}

		if (largest != node) {
			swap(largest, node);
			sink(largest);
		}
	}

	static void exchangeChildren(Node* first, Node* second) {
		if (second->left != 0) {
			second->left->parent = first;
		}
		if (second->right != 0) {
			second->right->parent = first;
		}
		Node* left = first->left;
		Node* right = first->right;
		first->left = second->left;
		first->right = second->right;
		second->left = left;
		second->right = right;
		if (left != 0) {
			left->parent = second;
		}
		if (right != 0) {
			right->parent = second;
		}
	}

	void swapSeparateNodes(Node* first, Node* second) {
		bool isLeftChild = second->isLeftChild();
		Node* parent = second->parent;

		if (first->isLeftChild()) {
			first->parent->left = second;
		} else if (first->isRightChild()) {
			first->parent->right = second;
		} else {
			root = second;
		}
		second->parent = first->parent;
		if (parent == 0) {
			root = first;
		} else if (isLeftChild) {
			parent->left = first;
		} else {
			parent->right = first;
		}
	}

	/**
	 *                               grandpa
	 *                                  |
	 *                                parent
	 *                                /    \
	 *                             child  brother
	 *                             /    \
	 *                           left  right
	 */
	// XXX Duplication to swapRightChildAndParent()
	void swapLeftChildAndParent(Node* child, Node* parent) {
		Node* grandpa = parent->parent;
		Node* brother = parent->right;
		Node* left = child->left;
		Node* right = child->right;

		parent->left = left;
		parent->right = right;
		child->right = brother;

		if (parent->isLeftChild()) {
			grandpa->left = child;
		} else if (parent->isRightChild()) {
			grandpa->right = child;
		} else {
			root =  child;
		}
		child->parent = grandpa;
		child->left = parent;
		parent->parent = child;

		if (left != 0) {
			left->parent = parent;
		}
		if (right != 0) {
			right->parent = parent;
		}
		if (brother != 0) {
			brother->parent = child;
		}
	}

	/**
	 *                           grandpa
	 *                              |
	 *                            parent
	 *                            /    \
	 *                       brother  child
	 *                                /   \
	 *                             left   right
	 */
	// XXX Duplication to swapLeftChildAndParent
	void swapRightChildAndParent(Node* child, Node* parent) {
		Node* grandpa = parent->parent;
		Node* brother = parent->left;
		Node* left = child->left;
		Node* right = child->right;

		parent->left = left;
		parent->right = right;
		child->left = brother;

		if (parent->isLeftChild()) {
			grandpa->left = child;
		} else if (parent->isRightChild()) {
			grandpa->right = child;
		} else {
			root = child;
		}
		child->parent = grandpa;
		child->right = parent;
		parent->parent = child;

		if (left != 0) {
			left->parent = parent;
		}
		if (right != 0) {
			right->parent = parent;
		}
		if (brother != 0) {
			brother->parent = child;
		}
	}

	// XXX swap() shouldn't be this complex? swap() of a typical array heap is very simple
	// XXX Find minimal size of a node, where swapping pointers is faster than swapping data
	//     members.
	void swap(Node* first, Node* second) {
		if (first == second) {
			return;
		}

		if (first->parent == second) {
			if (first->isLeftChild()) {
				swapLeftChildAndParent(first, second);
			} else {
				swapRightChildAndParent(first, second);
			}
		} else if (second->parent == first) {
			swap(second, first);
		} else {
			exchangeChildren(first, second);
			swapSeparateNodes(first, second);
		}
	}
};

} // namespace kernel

#endif // KERNEL_MM_MAX_HEAP_H_INCLUDED
