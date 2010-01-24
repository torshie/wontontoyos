#ifndef KERNEL_ARCH_NULL_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_NULL_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>

namespace kernel {

/**
 * Null Descriptor
 *
 * As required by the CPU specification, the first entry in Global
 * Descriptor Table must be a Null Descriptor
 */
struct NullDescriptor {
	friend class GlobalDescriptorTable;
private:
	U64 i;

	NullDescriptor() : i(0) {}

	NullDescriptor(const NullDescriptor&);
	const NullDescriptor& operator = (const NullDescriptor&);
} __attribute__((packed));

} /* namespace kernel */

#endif /* KERNEL_ARCH_NULL_DESCRIPTOR_H_INCLUDED */
