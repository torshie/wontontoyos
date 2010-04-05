#ifndef KERNEL_ARCH_NULL_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_NULL_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class NullDescriptor {
	friend class GlobalDescriptorTable;

	U64 initializer;

	NullDescriptor() : initializer(0) {}

	NullDescriptor(const NullDescriptor&);
	const NullDescriptor& operator = (const NullDescriptor&);
} __attribute__((packed));

} // namespace kernel

#endif // KERNEL_ARCH_NULL_DESCRIPTOR_H_INCLUDED
