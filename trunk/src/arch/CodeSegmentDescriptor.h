#ifndef __WONTON_KERNEL_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED__
#define __WONTON_KERNEL_CODE_SEGMENT_DESCRIPTOR_H_INCLUDED__

#include <base/type.h>

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
	base::U64 data; /** Used for initialize the descriptor to zero */
public:
	struct {
		base::U32 _zero0;
		base::U8 _zero1;
		base::U8 _zero2:2;
		base::U8 conforming:1;
		base::U8 _one0:1;
		base::U8 _one1:1;
		base::U8 dpl:2;
		base::U8 present:1;
		base::U8 _zero3:5;
		base::U8 longMode:1;
		base::U8 _zero4:1;
		base::U8 _zero5:1;
		base::U8 _zero6;
	} __attribute__((packed));
private:
	CodeSegmentDescriptor() : data(0), _one0(1), _one1(1),
		present(1), longMode(1) {}

	CodeSegmentDescriptor(const CodeSegmentDescriptor&);
	const CodeSegmentDescriptor& operator = (
			const CodeSegmentDescriptor&);
} __attribute__((packed));

namespace internal {
/**
 * Used to make sure the data structure is correctly packed
 * The use of the function is a little tricky: if the the data
 * data structure isn't packed as expected, we will get compile time
 * error. So, no need to implement this function, we just declare
 * it.
 */
void __checkStructureSize(char check
		[sizeof(CodeSegmentDescriptor) == 8 ? 1 : -1]);

}

}

#endif
