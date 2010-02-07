#ifndef KERNEL_ARCH_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>

namespace kernel {

/**
 * Code Segment Descriptor
 *
 * See AMD/Intel's system programming manual for more detailed
 * information
 */
union CodeSegmentDescriptor {
	friend class GlobalDescriptorTable;
private:
	U64 data; /* Used to initialize the descriptor */
public:
	struct {
		U32 _zero0;
		U8 _zero1;
		U8 _zero2:2;
		U8 conforming:1;
		U8 _one0:1;
		U8 _one1:1;
		U8 dpl:2;
		U8 present:1;
		U8 _zero3:5;
		U8 longMode:1;
		U8 _zero4:1;
		U8 _zero5:1;
		U8 _zero6;
	} __attribute__((packed));
private:
	CodeSegmentDescriptor() : data(0), _one0(1), _one1(1), present(1), longMode(1) {}

	CodeSegmentDescriptor(const CodeSegmentDescriptor&);
	const CodeSegmentDescriptor& operator = (const CodeSegmentDescriptor&);
} __attribute__((packed));

namespace internal {
/**
 * Used to make sure the data structure is correctly packed.
 *
 * If the data structure isn't packed as expected, we will get compile
 * time error.
 */
typedef int StaticSizeChecker[sizeof(CodeSegmentDescriptor) == 8 ? 1 : -1];

} /* namespace internal */

} /* namespace kernel */

#endif /* KERNEL_ARCH_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED */
