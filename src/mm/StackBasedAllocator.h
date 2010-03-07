#ifndef KERNEL_MM_STACK_BASED_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_STACK_BASED_ALLOCATOR_H_INCLUDED

#include "SimpleStack.h"
#include "Message.h"
#include <generic/type.h>
#include <generic/OFFSET_OF.h>
#include <cxx/new.h>

namespace kernel {

template<Size SLICE_SIZE> class StackBasedAllocator {
	friend class TestStackBasedAllocator;
	typedef char Load[SLICE_SIZE];
public:

#if defined(BUILD_TEST_MODE_KERNEL)
	int counter;

	StackBasedAllocator() : counter(0) {}
	~StackBasedAllocator() {
		if (counter != 0) {
			Message::critical << "StackBasedAllocator<" << (int)SLICE_SIZE << ">::counter == "
					<< counter << "\n";
		}
	}
#endif

	void addPool(void* pool, Size poolSize);
	void* allocate(Size size);
	void release(void* pointer);

private:
	SimpleStack<Load> stack;
};

template<Size SLICE_SIZE> void StackBasedAllocator<SLICE_SIZE>::addPool(void* pool,
		Size poolSize) {
	for (char* position = (char*)pool;
			position <= (char*)pool + poolSize - sizeof(typename SimpleStack<Load>::Node);
			position += sizeof(typename SimpleStack<Load>::Node)) {
		typename SimpleStack<Load>::Node* node =
				new (position) (typename SimpleStack<Load>::Node)();
		stack.push(node);
	}
}

template<Size SLICE_SIZE> void* StackBasedAllocator<SLICE_SIZE>::allocate(Size size) {
	if (size != SLICE_SIZE) {
		return 0;
	}

	typename SimpleStack<Load>::Node* node = stack.pop();
	if (node == 0) {
		return 0;
	} else {

#if defined(BUILD_TEST_MODE_KERNEL)
		++counter;
#endif

		return &(node->load);
	}
}

template<Size SLICE_SIZE> void StackBasedAllocator<SLICE_SIZE>::release(void* pointer) {
#ifdef BUILD_TEST_MODE_KERNEL
	--counter;
#endif

	void* tmp = (char*)pointer - OFFSET_OF(typename SimpleStack<Load>::Node, load);
	typename SimpleStack<Load>::Node* node = new (tmp)(typename SimpleStack<Load>::Node)();
	stack.push(node);
}

} // namespace kernel

#endif // KERNEL_MM_STACK_BASED_ALLOCATOR_H_INCLUDED
