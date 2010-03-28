#include "TaskStateSegmentDescriptor.h"
#include <generic/type.h>
#include <generic/Utils.h>
#include "getProcessorInstance.h"
#include <kernel/abi.h>
#include "TaskStateSegment.h"

namespace kernel {

TaskStateSegmentDescriptor::TaskStateSegmentDescriptor() {
	TaskStateSegment& tss = getProcessorInstance<TaskStateSegment>();
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
	type = 9; // XXX Evil literal constants
}


} // namespace kernel
