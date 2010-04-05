#include "TaskStateSegmentDescriptor.h"
#include <generic/type.h>
#include <generic/Utils.h>
#include "getProcessorInstance.h"
#include "TaskStateSegment.h"

namespace kernel {

extern "C" int __ld_image_start;
TaskStateSegmentDescriptor::TaskStateSegmentDescriptor() {
	TaskStateSegment& tss = getProcessorInstance<TaskStateSegment>();
	tss.rsp[0] = (Address)&__ld_image_start;
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
