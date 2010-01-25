#ifndef KERNEL_GENERIC_LIST_H_INCLUDED
#define KERNEL_GENERIC_LIST_H_INCLUDED

namespace kernel {

template<typename Payload, typename Allocator>
class List {
private:
	struct Node {
		Node* next;
		Node* prev;
		Payload payload;
	};

public:
	class Iterator {
		friend class List<Payload, Allocator>;
	public:
		Iterator() : node(0) {}

		Iterator operator ++ () {
			node = node->next;
			return node;
		}

		Iterator operator -- () {
			node = node->prev;
			return node;
		}

		bool operator == (Iterator i) const {
			return node == i.node;
		}

		bool operator != (Iterator i) const {
			return !(*this == i);
		}

	private:
		Node* node;
		Iterator(Node* n) : node(n) {}
	};

	List(Allocator& a) : head(&null), last(&null), allocator(a) {
		null.next = &null;
		null.prev = &null;
	}

	/**
	 * XXX Optimize
	 */
	~List() {
		erase(begin(), end());
	}

	Iterator begin() {
		return head;
	}

	Iterator end() {
		return &null;
	}

	void insert(Iterator position, const Payload& payload) {
		Node* node = static_cast<Node*>(allocator.allocate(sizeof(Node)));
		node->payload = payload;

		Node* tmp = position.node->next;
		node->next = tmp;
		tmp->prev = node;

		position.node->next = node;
		node->prev = position.node;
	}

	void insert(const Payload& payload, Iterator position) {
		insert(--position, payload);
	}

	void erase(Iterator position) {
		if (position.node == &null) {
			return;
		}
		position.node->next->prev = position.node->prev;
		position.node->prev->next = position.node->next;

		allocator.release(position.node);
	}

	void erase(Iterator first, Iterator last) {
		for (Iterator i = first; i != last && i != end(); ++i) {
			erase(i);
		}
	}

	bool isEmpty() const {
		return head == &null;
	}

private:
	Node null;
	Node* head;
	Allocator& allocator;
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_LIST_H_INCLUDED */
