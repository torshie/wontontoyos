#ifndef KERNEL_ARCH_TASK_STATE_SEGMENT_DESCRIPTOR_H_INCLUDED
#define KERNEL_ARCH_TASK_STATE_SEGMENT_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>
#include <generic/Utils.h>
#include <generic/getSingleInstance.h>
#include <kernel/abi.h>
#include "TaskStateSegment.h"

namespace kernel {

struct TaskStateSegmentDescriptor {
	friend class GlobalDescriptorTable;

	U16 segmentLimit0;
	U16 base0;
	U8 base1;
	U8 type:4;
	U8 _zero0:1;
	U8 dpl:2;
	U8 present:1;
	U8 segmentLimit1:4;
	U8 ignored:3;
	U8 granularity:1;
	U8 base2;
	U32 base3;
	U32 _zero1;

	TaskStateSegmentDescriptor() {
		TaskStateSegment& tss = getSingleInstance<TaskStateSegment>();
		tss.rsp[0] = KERNEL_VIRTUAL_BASE + KERNEL_PHYSICAL_BASE;
		Utils::zeroize(this, sizeof(TaskStateSegmentDescriptor));
		present = 1;
		Size limit = sizeof(tss) - 1;
		segmentLimit0 = limit;
		segmentLimit1 = limit >> 16;
		base0 = (Address)&tss;
		base1 = ((Address)&tss) >> 16;
		base2 = ((Address)&tss) >> 24;
		base3 = ((Address)&tss) >> 32;
		type = 9;
	}

	TaskStateSegmentDescriptor(const TaskStateSegmentDescriptor&);
	const TaskStateSegmentDescriptor& operator = (const TaskStateSegmentDescriptor&);
} __attribute__((packed));

STATIC_ASSERT_EQUAL(sizeof(TaskStateSegmentDescriptor), 16)

} /* namespace kernel */

#endif /* KERNEL_ARCH_TASK_STATE_SEGMENT_DESCRIPTOR_H_INCLUDED */
