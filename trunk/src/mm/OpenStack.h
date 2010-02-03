#ifndef KERNEL_GENERIC_OPEN_STACK_H_INCLUDED
#define KERNEL_GENERIC_OPEN_STACK_H_INCLUDED

namespace kernel {

template<typename Payload>
class OpenStack {
public:
	struct Node {
		Payload payload;
		Node* next;
	};

	OpenStack() : top(0) {}

	void push(Node* node) {
		node->next = top;
		top = node;
	}

	Node* getTop() const {
		return top;
	}

	void pop() {
		if (!isEmpty()) {
			top = top->next;
		}
	}

	bool isEmpty() const {
		return top == 0;
	}

private:
	Node* top;
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_OPEN_STACK_H_INCLUDED */
