#ifndef KERNEL_MM_MAX_HEAP_H_INCLUDED
#define KERNEL_MM_MAX_HEAP_H_INCLUDED

#include "StackBasedAllocator.h"
#include "TreeNodeHelper.h"
#include <cxx/BUG.h>

namespace kernel {

template<typename Key, typename Data, typename Allocator> class MaxHeap;
template<typename Key, typename Data> class HeapNode {
	template<typename A, typename B, typename C> friend class MaxHeap;
	friend class TreeNodeHelper;
	friend class TestMaxHeap;
	friend class GenericAllocator;

private:
	HeapNode* left;
	HeapNode* right;
	HeapNode* parent;

public:
	Key key;
	Data data;

	HeapNode(const Key& k, const Data& d) : left(0), right(0), parent(0), key(k), data(d) {}

private:
	template<typename Allocator> void releaseTree(Allocator& allocator) {
		TreeNodeHelper::releaseTree(this, allocator);
	}

	bool isLeftChild() const {
		return TreeNodeHelper::isLeftChild(this);
	}

	bool isRightChild() const {
		return TreeNodeHelper::isRightChild(this);
	}

	void setLeftChild(HeapNode* left) {
		TreeNodeHelper::setLeftChild(this, left);
	}

	void setRightChild(HeapNode* right) {
		TreeNodeHelper::setRightChild(this, right);
	}

	void replaceWith(HeapNode* replacement) {
		TreeNodeHelper::replaceWith(this, replacement);
	}
};

// XXX Refine access privileges of the members
// XXX Thread-safety
template<typename Key, typename Data,
		typename AllocatorParameter =
				StackBasedAllocator<sizeof(HeapNode<Key, Data>)> >
class MaxHeap {
	friend class TestMaxHeap;
public:
	typedef HeapNode<Key, Data> Node;
	typedef AllocatorParameter Allocator;

	MaxHeap(Allocator& alloc) : root(0), nodeCount(0), allocator(alloc) {}

	~MaxHeap() {
		root->releaseTree(allocator);
	}

	Node* insert(const Key& key, const Data& data) {
		void* buffer = allocator.allocate(sizeof(Node));
		HeapNode<Key, Data>* node = new (buffer) Node(key, data);

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
				root->~Node();
				allocator.release(root);
				root = 0;
			} else {
				BUG("node != root");
			}
			return;
		}

		Node* parentOfLastNode = getParentNode(nodeCount + 1);
		Node* lastNode;
		bool isLeftChild = (parentOfLastNode->right == 0);
		if (isLeftChild) {
			lastNode = parentOfLastNode->left;
		} else {
			lastNode = parentOfLastNode->right;
		}

		node->key = lastNode->key;
		node->data = lastNode->data;

		if (isLeftChild) {
			lastNode->parent->left = 0;
		} else {
			lastNode->parent->right = 0;
		}
		lastNode->~Node();
		allocator.release(lastNode);

		sink(node);
	}

	Node* decrease(Node* node, const Key& key) {
		node->key -= key;
		return sink(node);
	}

	Node* increase(Node* node, const Key& key) {
		node->key += key;
		return bubble(node);
	}

	Node* peek() {
		return root;
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

	Node* bubble(Node* node) {
		if ((node == root) || (node->key <= node->parent->key)) {
			return node;
		}

		Node* parent = node->parent;
		swap(node, parent);
		return bubble(parent);
	}

	Node* sink(Node* node) {
		Node* largest = node;
		if (node->left != 0 && largest->key < node->left->key) {
			largest = node->left;
		}
		if (node->right != 0 && largest->key < node->right->key) {
			largest = node->right;
		}

		if (largest != node) {
			swap(largest, node);
			return sink(largest);
		} else {
			return node;
		}
	}

	void swap(Node* first, Node* second) {
		if (first == second) {
			return;
		}
		Data data = first->data;
		Key key = first->key;
		first->data = second->data;
		first->key = second->key;
		second->data = data;
		second->key = key;
	}

#ifdef ENABLE_RUNTIME_CHECK
	void checkMaxHeap() {
		if (getHeapHeight() < 0) {
			BUG("checkMaxHeap() failed");
		}
	}

	int getHeapHeight() const {
		return getHeapHeight(root);
	}

	static int getHeapHeight(const Node* node) {
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
#endif

};

} // namespace kernel

#endif // KERNEL_MM_MAX_HEAP_H_INCLUDED
