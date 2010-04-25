#include "GenericAllocator.h"
#include "Message.h"

namespace kernel {

void* GenericAllocator::allocate(Size size) {
	size = Utils::roundUp(size, ROUND);
	if (size < heap.peek()->key) {
		Tree::Node* treeNode = (Tree::Node*)(heap.peek()->data);
		Heap::Node* heapNode = heap.decrease(heap.peek(), size);
		Address address = treeNode->key + heapNode->key;
		tree.insert(address, 0);
		return (void*)address;
	} else {
		// XXX Call PageMap::create to extend kernel linear address space instead of return 0
		return 0;
	}
}

void GenericAllocator::release(void* address) {
	Tree::Node* treeNode = tree.search((Address)address);
	if (treeNode == 0) {
		BUG("Bad release: " << address);
	}

	Heap::Node* heapNode = heap.insert(getMemorySliceSize(treeNode), treeNode);
	treeNode->data = heapNode;

	Tree::Node* successor = Tree::getSuccessor(treeNode);
	if (successor != 0 && successor->data != 0) {
		merge(treeNode, successor);
	}

	Tree::Node* predecessor = Tree::getPredecessor(treeNode);
	if (predecessor != 0 && predecessor->data != 0) {
		merge(predecessor, treeNode);
	}
}

void GenericAllocator::merge(Tree::Node* firstTreeNode, Tree::Node* secondTreeNode) {
	Heap::Node* firstHeapNode = (Heap::Node*)(firstTreeNode->data);
	Heap::Node* secondHeapNode = (Heap::Node*)(secondTreeNode->data);
	Size secondMemorySliceSize = secondHeapNode->key;
	heap.remove(secondHeapNode);
	tree.remove(secondTreeNode);
	firstHeapNode = heap.increase(firstHeapNode, secondMemorySliceSize);
	firstTreeNode->data = firstHeapNode;
}

Size GenericAllocator::getMemorySliceSize(const Tree::Node* node) const {
	if (node->data != 0) {
		return ((Heap::Node*)node->data)->key;
	}
	Tree::Node* successor = Tree::getSuccessor(node);
	if (successor != 0) {
		return successor->key - node->key;
	} else {
		return linearAddressEnd - node->key;
	}
}

} // namespace kernel
