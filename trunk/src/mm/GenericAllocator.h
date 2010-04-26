#ifndef KERNEL_MM_GENERIC_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_GENERIC_ALLOCATOR_H_INCLUDED

#include "MaxHeap.h"
#include "SearchTree.h"
#include "PageMap.h"
#include "PageTable.h"
#include "arch/X64Constant.h"

namespace kernel {

/**
 * XXX This is a hack, try to remove it. Probably a new design of MaxHeap & SearchTree is needed.
 *
 * The default MaxHeap::swap cannot be used by GenericAllocator, because of the internal of our
 * GenericAllocator. So specialization is used to override the default MaxHeap::swap.
 */
template<>
inline void MaxHeap<Size, void*, StackBasedAllocator<sizeof(HeapNode<Size, void*>)> >::swap(
		Node* first, Node* second) {
	typedef SearchTree<Address, void*>::Node TreeNode;
	TreeNode* firstTreeNode = (TreeNode*)(first->data);
	TreeNode* secondTreeNode = (TreeNode*)(second->data);
	firstTreeNode->data = second;
	secondTreeNode->data = first;

	Size key = first->key;
	void* data = first->data;
	first->key = second->key;
	first->data = second->data;
	second->key = key;
	second->data = data;
}

extern "C" int __ld_image_end;

// XXX Thread-safety
class GenericAllocator {
	friend GenericAllocator& getSingleInstance<GenericAllocator>();

	/**
	 * XXX We need some C++ syntax expert here. In the SearchTree, the void* is in fact a
	 * pointer to a node in the MaxHeap. Replace void* with some concrete type. Do the same to
	 * MaxHeap.
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
