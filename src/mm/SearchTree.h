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
	friend class GenericAllocator;

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
// XXX Remove duplication.
template<typename Key, typename Data,
		typename MemoryAllocator = StackBasedAllocator<sizeof(RedBlackTreeNode<Key, Data>)> >
class SearchTree {
	friend class TestSearchTree;
public:
	typedef MemoryAllocator Allocator;
	typedef RedBlackTreeNode<Key, Data> Node;

	explicit SearchTree(Allocator& alloc) : root(0), allocator(alloc) {}

	~SearchTree() {
		root->releaseTree(allocator);
	}

	Node* insert(const Key& key, const Data& data);

	void remove(Node* node) {
		Node* cursor = 0;
		if (node->left == 0 || node->right == 0) {
			cursor = node;
		} else {
			cursor = getSuccessor(node);
		}

		Node* child = 0;
		if (cursor->left != 0) {
			child = cursor->left;
		} else {
			child = cursor->right;
		}

		Node* fix = 0;
		bool left = false;;
		if (cursor != root) {
			fix = cursor->parent;
			if (cursor->isLeftChild()) {
				left = true;
			} else {
				left = false;
			}
			cursor->replaceWith(child);
		} else {
			root = child;
			if (root != 0) {
				root->parent = 0;
			}
		}

		bool isBlack = Node::isBlack(cursor);
		if (cursor != node) {
			if (node != root) {
				node->replaceWith(cursor);
			} else {
				root = cursor;
				root->parent = 0;
			}
			cursor->setLeftChild(node->left);
			cursor->setRightChild(node->right);
			cursor->red = node->red;
		}

		if (isBlack) {
			if (fix != 0) {
				fixUpRemove(fix, left);
			}
		}

		if (root != 0) {
			root->red = false;
		}

		node->~Node();
		allocator.release(node);

#ifdef BUILD_TEST_MODE_KERNEL
		checkRedBlackTree();
#endif
	}

private:
	Node* root;
	Allocator& allocator;

	void leftRotate(Node* node);
	void rightRotate(Node* child);
	void fixUpInsert(Node* node);

	static Node* getMinimum(Node* node) {
		Node* cursor = node;
		while (cursor->left != 0) {
			cursor = cursor->left;
		}
		return cursor;
	}

	static Node* getSuccessor(Node* node) {
		if (node->right != 0) {
			return getMinimum(node->right);
		} else {
			Node* parent = node->parent;
			while (parent != 0 && parent->right == node) {
				node = parent;
				parent = node->parent;
			}
			return parent;
		}
	}

	void fixUpRemove(Node* fix, bool left) {
		while (fix != 0) {
			if (left) {
				Node* child = fix->left;
				if (Node::isRed(child)) {
					child->red =false;
					break;
				}

				Node* cursor = fix->right;
				if (Node::isRed(cursor)) {
					cursor->red = false;
					fix->red = true;
					cursor = fix;
					leftRotate(fix);
				}
				if (Node::isBlack(cursor->left) && Node::isBlack(cursor->right)) {
					cursor->red = true;
					if (cursor->parent->isLeftChild()) {
						left = true;
					} else {
						left = false;
					}
					fix = cursor->parent->parent;
				} else {
					if (Node::isBlack(cursor->right)) {
						cursor->left->red = false;
						cursor->red = true;
						cursor = cursor->left;
						rightRotate(cursor->left);
					}
					cursor->red = cursor->parent->red;
					cursor->parent->red = false;
					leftRotate(cursor->parent);
					fix = 0;
				}
			} else {
				Node* child = fix->right;
				if (Node::isRed(child)) {
					child->red = false;
					break;
				}

				Node* cursor = fix->left;
				if (Node::isRed(cursor)) {
					cursor->red = false;
					fix->red = true;
					cursor = fix;
					rightRotate(fix);
				}
				if (Node::isBlack(cursor->left) && Node::isBlack(cursor->right)) {
					cursor->red = true;
					if (cursor->parent->isLeftChild()) {
						left = true;
					} else {
						left = false;
					}
					fix = cursor->parent->parent;
				} else {
					if (Node::isBlack(cursor->left)) {
						cursor->right->red = false;
						cursor->red = true;
						cursor = cursor->right;
						leftRotate(cursor->right);
					}
					cursor->red = cursor->parent->red;
					cursor->parent->red = false;
					rightRotate(cursor->parent);
					fix = 0;
				}
			}
		}
	}

#ifdef BUILD_TEST_MODE_KERNEL
	void checkRedBlackTree() {
		int height = getBlackHeight(root);
		if (height < 0) {
			BUG("SearchTree isn't a valid red-black tree.");
		}
	}

	static int getBlackHeight(Node* node) {
		if (node == 0) {
			return 0;
		}

		int leftBlackHeight = getBlackHeight(node->left);
		int rightBlackHeight = getBlackHeight(node->right);
		if (leftBlackHeight != rightBlackHeight || leftBlackHeight == -1
				|| rightBlackHeight == -1) {
			return -1;
		}

		if (node->left != 0) {
			if (node->left->key > node->key || node->left->parent != node) {
				return -1;
			}
		}
		if (node->right != 0) {
			if (node->right->key < node->key || node->right->parent  != node) {
				return -1;
			}
		}

		if (Node::isRed(node)) {
			if (Node::isRed(node->left) || Node::isRed(node->right)) {
				return -1;
			}
			return leftBlackHeight;
		} else {
			return leftBlackHeight + 1;
		}
	}
#endif

};

/**
 *                          |             leftRotate()               |
 *                         node          ===============>          child
 *                        /    \                                   /   \
 *                      left   child     <===============        node   right
 *                             /   \      rightRotate()         /    \
 *                         middle  right                      left  middle
 */
template<typename Key, typename Data, typename MemoryAllocator>
void SearchTree<Key, Data, MemoryAllocator>::leftRotate(Node* node) {
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

template<typename Key, typename Data, typename MemoryAllocator>
void SearchTree<Key, Data, MemoryAllocator>::rightRotate(Node* child) {
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

template<typename Key, typename Data, typename MemoryAllocator>
RedBlackTreeNode<Key, Data>* SearchTree<Key, Data, MemoryAllocator>::insert(const Key& key,
		const Data& data) {
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
		fixUpInsert(node);
	} else {
		root = node;
	}

	root->red = false;

#ifdef BUILD_TEST_MODE_KERNEL
		checkRedBlackTree();
#endif

	return node;
}

template<typename Key, typename Data, typename MemoryAllocator>
void SearchTree<Key, Data, MemoryAllocator>::fixUpInsert(Node* node) {
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

} // namespace kernel

#endif // KERNEL_MM_SEARCH_TREE_H_INCLUDED
