#ifndef KERNEL_MM_SIMPLE_STACK_H_INCLUDED
#define KERNEL_MM_SIMPLE_STACK_H_INCLUDED

namespace kernel {

template <typename Load> class SimpleStack {
public:
	struct Node {
		friend class SimpleStack<Load>;
		Load load;
	private:
		Node* next;
	};

	SimpleStack() : top(0) {}

	void push(Node* node) {
		node->next = top;
		top = node;
	}

	Node* pop() {
		Node* result = top;
		top = top->next;
		return result;
	}

	Node* peek() const {
		return top;
	}

private:
	Node* top;
};

} // namespace kernel

#endif // KERNEL_MM_SIMPLE_STACK_H_INCLUDED
