#ifndef KERNEL_MM_GENERIC_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_GENERIC_ALLOCATOR_H_INCLUDED

#include "MaxHeap.h"
#include "SearchTree.h"
#include "PageMap.h"
#include "PageTable.h"
#include "arch/X64Constant.h"

namespace kernel {

extern "C" char __ld_image_end;

// XXX Thread-safety
class GenericAllocator {
	friend GenericAllocator& getSingleInstance<GenericAllocator>();

	/** XXX In the SearchTree, the void* is in fact a pointer to a node in the MaxHeap. Replace
	 * void* with some concrete type. The same to MaxHeap.
	 */
	typedef SearchTree<Address, void*> Tree;
	typedef MaxHeap<Size, void*> Heap;

	char treeBootBuffer[PAGE_SIZE];
	char heapBootBuffer[PAGE_SIZE];
	Tree::Allocator treeNodeAllocator;
	Heap::Allocator heapNodeAllocator;
	Tree tree;
	Heap heap;
	Address linearAddressEnd;

	enum {
		CHUNK_SIZE = 32 * 1024 * 1024,
		ROUND = 8
	};

	GenericAllocator() : treeNodeAllocator(treeBootBuffer, sizeof(treeBootBuffer)),
			heapNodeAllocator(heapBootBuffer, sizeof(heapBootBuffer)), tree(treeNodeAllocator),
			heap(heapNodeAllocator), linearAddressEnd((Address)&__ld_image_end) {
		Heap::Node* heapNode = heap.insert(CHUNK_SIZE, 0);
		Tree::Node* treeNode = tree.insert(linearAddressEnd, heapNode);
		heapNode->data = treeNode;
		PageMap::create(linearAddressEnd, CHUNK_SIZE);
		linearAddressEnd += CHUNK_SIZE;
	}

public:
	void* allocate(Size size);
	void release(void* address);

private:
	void merge(Tree::Node* first, Tree::Node* second);
	Size getMemorySliceSize(const Tree::Node* node) const;
};

} // namespace kernel

#endif // KERNEL_MM_GENERIC_ALLOCATOR_H_INCLUDED
