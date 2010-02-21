#ifndef KERNEL_ARCH_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

/**
 * Code Segment Descriptor
 *
 * Referer to AMD/Intel's system programming manual for more detailed information
 */
union CodeSegmentDescriptor {
	friend class GlobalDescriptorTable;
private:
	U64 initializer; /* Used to initialize the descriptor */
public:
	struct {
		U64 __zero_0:42;
		U8 conforming:1;
		U8 __one_0:1;
		U8 __one_1:1;
		U8 dpl:2;
		U8 present:1;
		U8 __zero_1:5;
		U8 longMode:1;
		U16 __zero_2:10;
	} __attribute__((packed));
private:
	CodeSegmentDescriptor() : initializer(0), __one_0(1), __one_1(1), present(1), longMode(1) {}

	CodeSegmentDescriptor(const CodeSegmentDescriptor&);
	const CodeSegmentDescriptor& operator = (const CodeSegmentDescriptor&);
} __attribute__((packed));

STATIC_ASSERT_EQUAL(sizeof(CodeSegmentDescriptor), 8)

} /* namespace kernel */

#endif /* KERNEL_ARCH_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED */
