#ifndef KERNEL_GENERIC_STACK_BASED_ALLOCATOR_H_INCLUDED
#define KERNEL_GENERIC_STACK_BASED_ALLOCATOR_H_INCLUDED

#include <generic/type.h>
#include "OpenStack.h"
#include <cxx/new.h>

namespace kernel {

template<Size SLICE_SIZE>
class StackBasedAllocator {
	typedef char Payload[SLICE_SIZE];
	typedef OpenStack<Payload> Stack;
public:
	void takeControl(void* base, Size size) {
		enum {
			INCREMENTAL = sizeof(typename Stack::Node)
		};
		Size count = size / INCREMENTAL;
		char* tmp = static_cast<char*>(base);
		for (Size i = 0; i < count; ++i, tmp += INCREMENTAL) {
			available.push(new (tmp) typename Stack::Node());
		}
	}

	void* allocate(Size size = SLICE_SIZE) {
		if (size != SLICE_SIZE) {
			return 0;
		}
		typename Stack::Node* top = available.getTop();
		available.pop();
		if (top) {
			return top->payload;
		} else {
			return 0;
		}
	}

	void release(void* pointer) {
		static_cast<typename Stack::Node*>(pointer)->~Node();
		available.push(new (pointer) typename Stack::Node());
	}

private:
	Stack available;
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_STACK_BASED_ALLOCATOR_H_INCLUDED */
