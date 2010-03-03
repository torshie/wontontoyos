#ifndef KERNEL_MM_MAX_HEAP_H_INCLUDED
#define KERNEL_MM_MAX_HEAP_H_INCLUDED

#include "PageTable.h"
#include "PagePointer.h"
#include <kernel/abi.h>

namespace kernel {

// XXX Call copy constructors, call destructors.
template<typename Key, typename Data, typename Extender> class MaxHeap {
public:
	struct Node {
		Key key;
		Data data;
	};

	MaxHeap(void* buffer, Size size, Extender xtender) : bufferSize(size), nodeCount(0),
			base(buffer), extender(xtender) {}

	void insert(const Key& key, const Data& data) {
		if (full()) {
			extender.extend((char*)base + bufferSize, PAGE_SIZE);
			bufferSize += PAGE_SIZE;
		}

		base[nodeCount].key = key;
		base[nodeCount].data = data;
		bubble(nodeCount);
		nodeCount += 1;
	}

	void decrease(Size index, const Key& key) {
		base[index].key = base[index].key - key;
		sink(index);
	}

	void increase(Size index, const Key& key) {
		base[index].key = base[index].key + key;
		bubble(index);
	}

	void remove(Size index) {
		base[index].key = base[nodeCount - 1].key;
		base[index].data = base[nodeCount - 1].data;
		nodeCount -= 1;
		sink(index);
	}

	const Node* peek(Size index) const {
		if (index >= nodeCount) {
			return 0;
		} else {
			return base + index;
		}
	}

private:
	Size bufferSize;
	Size nodeCount;
	Node* base;
	Extender& extender;

	bool full() const {
		return (nodeCount + 1) * sizeof(Node) > bufferSize;
	}

	void sink(Size index) {
		bool hasLeftChild = (leftChild(index) < nodeCount);
		if (!hasLeftChild) {
			return;
		}
		bool hasRightChild = (rightChild(index) < nodeCount);

		Size largest = index;
		if (base[leftChild(index)].key > base[index].key) {
			largest = leftChild(index);
		}
		if (hasRightChild) {
			if (base[rightChild(index)].key > base[largest].key) {
				largest = rightChild(index);
			}
		}

		if (largest != index) {
			swap(index, largest);
			sink(largest);
		}
	}

	void bubble(Size index) {
		if (index == 0 || base[index].key < base[parent(index)].key) {
			return;
		}

		swap(index, parent(index));
		bubble(parent(index));
	}

	void swap(Size first, Size second) {
		Key key = base[first].key;
		Data data = base[first].data;
		base[first].key = base[second].key;
		base[first].data = base[second].data;
		base[second].key = key;
		base[second].data = data;
	}

	static Size leftChild(Size index) {
		return (index + 1) * 2 - 1;
	}

	static Size rightChild(Size index) {
		return (index + 1) * 2;
	}

	static Size parent(Size index) {
		return (index - 1) / 2;
	}
};

} // namespace kernel

#endif // KERNEL_MM_MAX_HEAP_H_INCLUDED
