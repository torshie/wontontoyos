#ifndef KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>
#include <sexy/STATIC_ASSERT.h>

namespace kernel {

union DataSegmentDescriptor {
	friend class GlobalDescriptorTable;
private:
	U64 initializer; /* Used to initialize the descriptor */
public:
	struct {
		U32 __zero_0;
		U8 __base_0;
		U8 accessed:1;
		U8 writable:1;
		U8 __ignored_0:2;
		U8 __one_0:1;
		U8 __dpl:2;
		U8 present:1;
		U16 __ignored_1;
	} __attribute__((packed));
private:
	DataSegmentDescriptor() : initializer(0), writable(1), __one_0(1), present(1) {}

	DataSegmentDescriptor(const DataSegmentDescriptor&);
	const DataSegmentDescriptor& operator = (const DataSegmentDescriptor&);
} __attribute__((packed));

STATIC_ASSERT_EQUAL(sizeof(DataSegmentDescriptor), 8)

} // namespace kernel

#endif // KERNEL_ARCH_DATA_SEGMENT_DESCRIPTOR_H_INCLUDED
