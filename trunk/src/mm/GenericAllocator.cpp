#include "GenericAllocator.h"

namespace kernel {

void* GenericAllocator::allocate(Size size) {
	size = Utils::roundUp(size, ROUND);
	if (size < heap.peek()->key) {
		Tree::Node* treeNode = (Tree::Node*)(heap.peek()->data);
		heap.decrease(heap.peek(), size);
		Address address = treeNode->key + heap.peek()->key;
		tree.insert(address, 0);
		return (void*)address;
	} else {
		// XXX Use PageMap::createKernelHierarchy to extend kernel linear address instead of
		//     return 0
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

	for (Tree::Node* successor = Tree::getSuccessor(treeNode);
			successor != 0 && successor->data != 0;
			successor = Tree::getSuccessor(treeNode)) {
		merge(treeNode, successor);
	}

	for (Tree::Node* predecessor = Tree::getPredecessor(treeNode);
			predecessor != 0 && predecessor->data != 0;
			treeNode = predecessor, predecessor = Tree::getPredecessor(treeNode)) {
		merge(predecessor, treeNode);
	}
}

void GenericAllocator::merge(Tree::Node* first, Tree::Node* second) {
	Heap::Node* secondHeapNode = (Heap::Node*)(second->data);
	Size secondSize = secondHeapNode->key;
	heap.remove(secondHeapNode);
	Heap::Node* firstHeapNode = (Heap::Node*)(first->data);
	heap.increase(firstHeapNode, secondSize);
	tree.remove(second);
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
