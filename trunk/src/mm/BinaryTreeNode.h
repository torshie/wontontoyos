#ifndef KERNEL_MM_BINARY_TREE_NODE_H_INCLUDED
#define KERNEL_MM_BINARY_TREE_NODE_H_INCLUDED

namespace kernel {

template<typename Key, typename Data, typename Allocator> class MaxHeap;
template<typename Key, typename Data, typename Allocator> class SearchTree;

template<typename Key, typename Data> class BinaryTreeNode {
	template<typename A, typename B, typename C> friend class MaxHeap;
	template<typename A, typename B, typename C> friend class SearchTree;
	friend class TestMaxHeap;
	friend class TestSearchTree;

	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode* parent;

public:
	Key key;
	Data data;

	BinaryTreeNode(const Key& k, const Data& d) : left(0), right(0), parent(0), key(k), data(d) {}

	bool isLeftChild() const {
		if (parent != 0) {
			return parent->left == this;
		} else {
			return false;
		}
	}

	bool isRightChild() const {
		if (parent != 0) {
			return parent->right == this;
		} else {
			return false;
		}
	}

private:
	template<typename Allocator> static void releaseTree(BinaryTreeNode* root,
			Allocator& allocator) {
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

			BinaryTreeNode* tmp = 0;
			if (node->isLeftChild()) {
				tmp = node->parent->left;
				node->parent->left = 0;
			} else if (node->isRightChild()) {
				tmp = node->parent->right;
				node->parent->right = 0;
			}

			if (node != root) {
				node = node->parent;
				tmp->~BinaryTreeNode();
				allocator.release(tmp);
			} else {
				node->~BinaryTreeNode();
				allocator.release(node);
				break;
			}
		}
	}
};

} // namespace kernel

#endif // KERNEL_MM_BINARY_TREE_NODE_H_INCLUDED
