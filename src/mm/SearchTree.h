#ifndef KERNEL_MM_SEARCH_TREE_H_INCLUDED
#define KERNEL_MM_SEARCH_TREE_H_INCLUDED

#include "StackBasedAllocator.h"
#include "TreeNodeHelper.h"
#include <cxx/BUG.h>

namespace kernel {

template<typename Key, typename Data> class RedBlackTreeNode {
	template<typename A, typename B, typename C> friend class SearchTree;
	friend class TreeNodeHelper;
	friend class TestSearchTree;

	RedBlackTreeNode* left;
	RedBlackTreeNode* right;
	RedBlackTreeNode* parent;
	bool red;

public:
	Key key;
	Data data;

	RedBlackTreeNode(const Key& k, const Data& d) : left(0), right(0), parent(0), red(true),
			key(k), data(d) {}

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

	void setLeftChild(RedBlackTreeNode* left) {
		TreeNodeHelper::setLeftChild(this, left);
	}

	void setRightChild(RedBlackTreeNode* right) {
		TreeNodeHelper::setRightChild(this, right);
	}

	void replaceWith(RedBlackTreeNode* replacement) {
		TreeNodeHelper::replaceWith(this, replacement);
	}

	static bool isRed(RedBlackTreeNode* node) {
		if (node != 0) {
			return node->red;
		} else {
			return false;
		}
	}

	static bool isBlack(RedBlackTreeNode* node) {
		return !isRed(node);
	}
};

// XXX Make the tree implementation thread-safe
template<typename Key, typename Data,
		typename AllocatorParameter = StackBasedAllocator<sizeof(RedBlackTreeNode<Key, Data>)> >
class SearchTree {
	friend class TestSearchTree;
public:
	typedef AllocatorParameter Allocator;
	typedef RedBlackTreeNode<Key, Data> Node;

	explicit SearchTree(Allocator& alloc) : root(0), allocator(alloc) {}

	~SearchTree() {
		root->releaseTree(allocator);
	}

	Node* insert(const Key& key, const Data& data) {
		void* buffer = allocator.allocate(sizeof(Node));
		Node* node = new (buffer) Node(key, data);

		Node* cursor = root;
		if (root != 0) {
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
			insertFixUp(node);
		} else {
			root = node;
		}

		root->red = false;
		return node;
	}

private:
	Node* root;
	Allocator& allocator;

	/**
	 *                          |             leftRotate()               |
	 *                         node          ===============>          child
	 *                        /    \                                   /   \
	 *                      left   child     <===============        node   right
	 *                             /   \      rightRotate()         /    \
	 *                         middle  right                      left  middle
	 */
	void leftRotate(Node* node) {
		Node* child = node->right;
		Node* middle = child->left;

		if (root == node) {
			root = child;
			child->parent = 0;
		} else {
			node->replaceWith(child);
		}

		child->left = node;
		node->parent = child;

		node->setRightChild(middle);
	}

	void rightRotate(Node* child) {
		Node* node = child->left;
		Node* middle = node->right;

		if (root == child) {
			root = node;
			node->parent = 0;
		} else {
			child->replaceWith(node);
		}

		node->right = child;
		child->parent = node;

		child->setLeftChild(middle);
	}

	void insertFixUp(Node* node) {
		while (Node::isRed(node->parent)) {
			Node* parent = node->parent;
			Node* grandpa = parent->parent;
			if (parent->isLeftChild()) {
				/**
				 *                    grandpa(B)
				 *                    /       \
				 *               parent(R)   uncle(R/B)
				 *                 /
				 *             node(R)
				 */
				Node* uncle = grandpa->right;
				if (Node::isRed(uncle)) {
					parent->red = false;
					uncle->red = false;
					grandpa->red = true;
					node = grandpa;
				} else {
					if (node->isRightChild()) {
						leftRotate(node->parent);
						node = node->left;
					}
					node->parent->red = false;
					grandpa->red = true;
					rightRotate(grandpa);
				}
			} else {
				/**
				 *                    grandpa(B)
				 *                    /       \
				 *               uncle(R/B)   parent(R)
				 *                               \
				 *                              node(R)
				 */
				Node* uncle = grandpa->left;
				if (Node::isRed(uncle)) {
					uncle->red = false;
					parent->red = false;
					grandpa->red = true;
					node = grandpa;
				} else {
					if (node->isLeftChild()) {
						rightRotate(parent);
						node = node->right;
					}
					node->parent->red = false;
					grandpa->red = true;
					leftRotate(grandpa);
				}
			}
		}
	}
};

} // namespace kernel

#endif // KERNEL_MM_SEARCH_TREE_H_INCLUDED
