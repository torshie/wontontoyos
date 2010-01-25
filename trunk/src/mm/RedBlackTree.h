#ifndef KERNEL_MM_RED_BLACK_TREE_H_INCLUDED
#define KERNEL_MM_RED_BLACK_TREE_H_INCLUDED

class TestRedBlackTree;

template<typename Payload, typename Allocator>
class RedBlackTree {
	friend class TestRedBlackTree;
private:
	enum Color {
		BLACK, RED
	};

	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		Color color;
		Payload payload;
	};

public:
	RedBlackTree(Allocator& a) : allocator(a), root(&null) {
		null.parent = &null;
		null.left = &null;
		null.right = &null;
		null.color = BLACK;
	}

private:
	Allocator& allocator;
	Node null;
	Node* root;

	/**
	 *                   |          leftRotate           |
	 *                  (x)        ============>        (y)
	 *                 /   \       <============       /   \
	 *            (left)   (y)      rightRotate      (x)   (right)
	 *                    /   \                     /   \
	 *            (middle)     (right)        (left)    (middle)
	 */
	static void rightRotate(Node*& y) {
		Node* x = y->left;
		Node* middle = x->right;
		Node* right = y->right;

		y->left = middle;
		middle->parent = y;

		x->right = y;
		x->parent = y->parent;
		y->parent = x;
		y = x;
	}

	static void leftRotate(Node*& x) {
		Node* left = x->left;
		Node* y = x->right;
		Node* middle = y->left;

		x->right = middle;
		middle->parent = x;

		y->parent = x->parent;
		y->left = x;
		x->parent = y;
		x = y;
	}
};

#endif
