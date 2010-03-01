#ifndef KERNEL_MM_NULL_ALLOCATOR_H_INCLUDED
#define KERNEL_MM_NULL_ALLOCATOR_H_INCLUDED

namespace kernel {

class NullAllocator {
public:
	void* allocate(Size) {
		return 0;
	}

	void release(void*) {
	}
};

} // namespace kernel

#endif // KERNEL_MM_NULL_ALLOCATOR_H_INCLUDED
