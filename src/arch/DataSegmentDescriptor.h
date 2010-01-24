#ifndef KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>

namespace kernel {

/**
 * Data Segment Descriptor
 *
 * See AMD/Intel's system programming manual for more detailed
 * information
 */
union DataSegmentDescriptor {
	friend class GlobalDescriptorTable;
private:
	U64 data; /* Used to initialize the descriptor */
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
	DataSegmentDescriptor() : data(0), writable(1), _one0(1),
			present(1) {}

	DataSegmentDescriptor(const DataSegmentDescriptor&);
	const DataSegmentDescriptor& operator = (
			const DataSegmentDescriptor&);
} __attribute__((packed));

namespace internal {
/**
 * Used to make sure the data structure is correctly packed.
 *
 * If the data structure isn't packed as expected, we will get compile
 * time error.
 */
typedef int StaticSizeChecker[sizeof(DataSegmentDescriptor) == 8 ? 1 : -1];
} /* namespace internal */

} /* namespace kernel */

#endif /* KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED */
