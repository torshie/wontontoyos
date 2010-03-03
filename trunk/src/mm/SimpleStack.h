#ifndef KERNEL_MM_SIMPLE_STACK_H_INCLUDED
#define KERNEL_MM_SIMPLE_STACK_H_INCLUDED

namespace kernel {

template <typename Load> class SimpleStack {
public:
	class Node {
		friend class SimpleStack<Load>;
		Node* next;

	public:
		Load load;
	};

	SimpleStack() : top(0) {}

	void push(Node* node) {
		node->next = top;
		top = node;
	}

	Node* pop() {
		if (top == 0) {
			return 0;
		}

		Node* result = top;
		top = top->next;
		return result;
	}

	const Node* peek() const {
		return top;
	}

private:
	Node* top;
};

} // namespace kernel

#endif // KERNEL_MM_SIMPLE_STACK_H_INCLUDED
