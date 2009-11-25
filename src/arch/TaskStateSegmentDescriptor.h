#ifndef __WONTON_KERNEL_TASK_STATE_SEGMENT_DESCRIPTOR_H_INCLUDED__
#define __WONTON_KERNEL_TASK_STATE_SEGMENT_DESCRIPTOR_H_INCLUDED__

#include <base/type.h>
#include <base/Memory.h>
#include <base/getSingleInstance.h>
#include <kernel/abi.h>
#include "TaskStateSegment.h"

namespace kernel {

/**
 * Task State Segment Descriptor
 *
 * See AMD/Intel's system programming manual for more detailed
 * information
 */
struct TaskStateSegmentDescriptor {
	friend class GlobalDescriptorTable;
private:
	base::U16 segmentLimit0;
	base::U16 base0;
	base::U8 base1;
	base::U8 type:4;
	base::U8 _zero0:1;
	base::U8 dpl:2;
	base::U8 present:1;
	base::U8 segmentLimit1:4;
	base::U8 ignored:3;
	base::U8 granularity:1;
	base::U8 base2;
	base::U32 base3;
	base::U32 _zero1;

	TaskStateSegmentDescriptor() {
		TaskStateSegment& tss
				= base::getSingleInstance<TaskStateSegment>();
		tss.rsp[0] = KERNEL_VIRTUAL_BASE + KERNEL_LOAD_ADDRESS;
		base::Memory::zeroize(this, sizeof(TaskStateSegmentDescriptor));
		present = 1;
		base::Size limit = sizeof(tss) - 1;
		segmentLimit0 = limit;
		segmentLimit1 = limit >> 16;
		base0 = (base::Address)&tss;
		base1 = ((base::Address)&tss) >> 16;
		base2 = ((base::Address)&tss) >> 24;
		base3 = ((base::Address)&tss) >> 32;
		type = 9;
	}

	TaskStateSegmentDescriptor(const TaskStateSegmentDescriptor&);
	const TaskStateSegmentDescriptor& operator = (
			const TaskStateSegmentDescriptor&);
} __attribute__((packed));

namespace internal {
void __checkStructureSize(char check
		[sizeof(TaskStateSegmentDescriptor) == 16 ? 1 : -1]);
}

} /* namespace kernel */

#endif
