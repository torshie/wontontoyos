#ifndef KERNEL_MM_TREE_NODE_HELPER_H_INCLUDED
#define KERNEL_MM_TREE_NODE_HELPER_H_INCLUDED

namespace kernel {

template<typename A, typename B> class HeapNode;
template<typename A, typename B> class RedBlackTreeNode;

class TreeNodeHelper {
	template<typename A, typename B> friend class HeapNode;
	template<typename A, typename B> friend class RedBlackTreeNode;
	~TreeNodeHelper();

	template<typename TreeNode> static bool isLeftChild(TreeNode* node);
	template<typename TreeNode> static bool isRightChild(TreeNode* node);
	template<typename TreeNode> static void setLeftChild(TreeNode* node, TreeNode* left);
	template<typename TreeNode> static void setRightChild(TreeNode* node, TreeNode* right);
	template<typename TreeNode> static void replaceWith(TreeNode* node, TreeNode* replacement);
	template<typename TreeNode, typename Allocator> static void releaseTree(TreeNode* root,
			Allocator& allocator);
};

template<typename TreeNode> void TreeNodeHelper::replaceWith(TreeNode* node,
		TreeNode* replacement) {
	if (node->isLeftChild()) {
		node->parent->left = replacement;
	} else {
		node->parent->right = replacement;
	}
	if (replacement != 0) {
		replacement->parent = node->parent;
	}
}

template<typename TreeNode> void TreeNodeHelper::setLeftChild(TreeNode* node, TreeNode* left) {
	node->left = left;
	if (left != 0) {
		left->parent = node;
	}
}

template<typename TreeNode> void TreeNodeHelper::setRightChild(TreeNode* node, TreeNode* right) {
	node->right = right;
	if (right != 0) {
		right->parent = node;
	}
}

template<typename TreeNode> bool TreeNodeHelper::isLeftChild(TreeNode* node) {
	if (node->parent != 0) {
		return node->parent->left == node;
	} else {
		return false;
	}
}

template<typename TreeNode> bool TreeNodeHelper::isRightChild(TreeNode* node) {
	if (node->parent != 0) {
		return node->parent->right == node;
	} else {
		return false;
	}
}

template<typename TreeNode, typename Allocator>
void TreeNodeHelper::releaseTree(TreeNode* root, Allocator& allocator) {
	if (root == 0) {
		return;
	}

	TreeNode* node = root;
	while (true) {
		while (node->left != 0 || node->right != 0) {
			if (node->left != 0) {
				node = node->left;
			} else {
				node = node->right;
			}
		}

		TreeNode* tmp = 0;
		if (node->isLeftChild()) {
			tmp = node->parent->left;
			node->parent->left = 0;
		} else if (node->isRightChild()) {
			tmp = node->parent->right;
			node->parent->right = 0;
		}

		if (node != root) {
			node = node->parent;
			tmp->~TreeNode();
			allocator.release(tmp);
		} else {
			node->~TreeNode();
			allocator.release(node);
			break;
		}
	}
}

} // namespace kernel

#endif // KERNEL_MM_TREE_NODE_HELPER_H_INCLUDED
