#ifndef __WONTON_KERNEL_NULL_DESCRIPTOR_H_INCLUDED__
#define __WONTON_KERNEL_NULL_DESCRIPTOR_H_INCLUDED__

#include <base/type.h>

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
	base::U64 i;

	NullDescriptor() : i(0) {}

	NullDescriptor(const NullDescriptor&);
	const NullDescriptor& operator = (const NullDescriptor&);
} __attribute__((packed));

}

#endif
