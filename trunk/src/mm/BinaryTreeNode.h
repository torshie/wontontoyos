#ifndef KERNEL_MM_BINARY_TREE_NODE_H_INCLUDED
#define KERNEL_MM_BINARY_TREE_NODE_H_INCLUDED

namespace kernel {

template<typename Key, typename Data> struct BinaryTreeNode {
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	BinaryTreeNode* parent;
	Key key;
	Data data;

	BinaryTreeNode(const Key& k, const Data& d) : left(0), right(0), parent(0), key(k), data(d) {}
};

} // namespace kernel

#endif // KERNEL_MM_BINARY_TREE_NODE_H_INCLUDED
