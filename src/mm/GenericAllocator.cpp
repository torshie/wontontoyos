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
#ifdef BUILD_TEST_MODE_KERNEL
		++counter;
#endif
	} else {
		// XXX Use PageMap::createKernelHierarchy to extend kernel linear addres instead of
		//     return 0
		return 0;
	}
}

} // namespace kernel
