#ifndef __WONTON_KERNEL_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED__
#define __WONTON_KERNEL_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED__

#include <base/type.h>

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
	base::U64 data;
public:
	struct {
		base::U32 _zero0;
		base::U16 _base0:8;
		base::U8 accessed:1;
		base::U8 writable:1;
		base::U8 _ignored:2;
		base::U8 _one0:1;
		base::U8 _dpl:2;
		base::U8 present:1;
		base::U16 _ig;
	} __attribute__((packed));
private:
	DataSegmentDescriptor() : data(0), writable(1), _one0(1),
			present(1) {}

	DataSegmentDescriptor(const DataSegmentDescriptor&);
	const DataSegmentDescriptor& operator = (
			const DataSegmentDescriptor&);
} __attribute__((packed));

namespace internal {
void __checkStructureSize(char check
		[sizeof(DataSegmentDescriptor) == 8 ? 1 : -1]);
}

}

#endif
