#ifndef KERNEL_MM_SEARCH_TREE_H_INCLUDED
#define KERNEL_MM_SEARCH_TREE_H_INCLUDED

#include "mm/NullAllocator.h"
#include "mm/StackBasedAllocator.h"

namespace kernel {

// XXX Implement a red-black tree instead of a simple binary search tree
// XXX Make this thread-safe
template<typename Key, typename Data, typename Allocator> class SearchTree;

template<typename Key, typename Data,
		typename AllocatorParameter =
				StackBasedAllocator<sizeof(SearchTree<Key, Data, NullAllocator>)> >
class SearchTree {
	friend class TestSearchTree;
public:
	typedef AllocatorParameter Allocator;

	struct Node {
	private:
		Node* left;
		Node* right;
		Node* parent;
		Key key;

	public:
		Node(const Key& k, const Data& d) : left(0), right(0), parent(0), key(k), data(d) {}

		Data data;
	};

	explicit SearchTree(Allocator& alloc) : root(0), allocator(alloc) {}
	~SearchTree();

	void insert(const Key& key, const Data& data) {
		void* buffer = allocator.allocate(sizeof(Node));
		Node* node = new (buffer)Node(key, data);
		Node** cursor = &root;
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

	void remove(Node* node);
	void remove(const Key& key);

	Data* search(const Key& key) {
		Node* cursor = root;
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
	Node* root;
	Allocator& allocator;
};

} // namespace kernel

#endif // KERNEL_MM_SEARCH_TREE_H_INCLUDED
