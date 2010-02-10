#ifndef KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

/**
 * Data Segment Descriptor
 *
 * Referer to AMD/Intel's system programming manual for more detailed information
 */
union DataSegmentDescriptor {
	friend class GlobalDescriptorTable;
private:
	U64 initializer; /* Used to initialize the descriptor */
public:
	struct {
		U32 _zero0;
		U16 _base0:8;
		U8 accessed:1;
		U8 writable:1;
		U8 _ignored:2;
		U8 _one0:1;
		U8 _dpl:2;
		U8 present:1;
		U16 _ig;
	} __attribute__((packed));
private:
	DataSegmentDescriptor() : initializer(0), writable(1), _one0(1), present(1) {}

	DataSegmentDescriptor(const DataSegmentDescriptor&);
	const DataSegmentDescriptor& operator = (const DataSegmentDescriptor&);
} __attribute__((packed));

STATIC_ASSERT_EQUAL(sizeof(DataSegmentDescriptor), 8)

} /* namespace kernel */

#endif /* KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED */
