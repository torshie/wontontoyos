#ifndef KERNEL_MM_STACK_BASED_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_STACK_BASED_ALLOCATOR_H_INCLUDED

#include <generic/type.h>
#include <cxx/new.h>

namespace kernel {

template<Size SLICE_SIZE> class StackBasedAllocator {
	typedef char Load[SLICE_SIZE];
public:
	void addPool(void* pool, Size poolSize);
	void* allocate(Size size);
	void release(void* pointer);

private:
	SimpleStack<Load> stack;
};

template<Size SLICE_SIZE> void StackBasedAllocator<SLICE_SIZE>::addPool(void* pool,
		Size poolSize) {
	for (char* position = (char*)pool; position < (char*)pool + poolSize;
			position += sizeof(SimpleStack<Load>::Node)) {
		SimpleStack<Load>::Node* node = new (position)SimpleStack<Load>::Node();
		stack.push(node);
	}
}

template<Size SLICE_SIZE> void* StackBasedAllocator<SLICE_SIZE>::allocate(Size size) {
	if (size != SLICE_SIZE) {
		return 0;
	}

	return &(stack.pop()->load);
}

template<Size SLICE_SIZE> void StackBasedAllocator<SLICE_SIZE>::release(void* pointer) {
	SimpleStack<Load>::Node* node = new (pointer)SimpleStack<Load>::Node();
	stack.push(node);
}

} // namespace kernel

#endif // KERNEL_MM_STACK_BASED_ALLOCATOR_H_INCLUDED
