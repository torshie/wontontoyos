#ifndef KERNEL_ARCH_TASK_STATE_SEGMENT_H_INCLUDED
#define KERNEL_ARCH_TASK_STATE_SEGMENT_H_INCLUDED

#include <generic/type.h>
#include <generic/Utils.h>
#include "getProcessorInstance.h"

namespace kernel {

struct TaskStateSegment {
	friend TaskStateSegment& getProcessorInstance<TaskStateSegment>();
private:
	U32 reserved0;
public:
	U64 rsp[3];
	U64 ist[7]; // IST0 is reserved
private:
	U64 reserved1;
	U16 reserved2;
public:
	U16 ioMapBase;
	U8 ioMap[8192];

private:
	TaskStateSegment() {
		Utils::zeroize(this, sizeof(TaskStateSegment) - sizeof(ioMap));
		Utils::memset(ioMap, 0, sizeof(ioMap));
		ioMapBase = (char*)&ioMapBase - (char*)this;
	}

	TaskStateSegment(const TaskStateSegment&);
	const TaskStateSegment& operator = (const TaskStateSegment&);

} __attribute__((__packed__));

} // namespace kernel

#endif // KERNEL_ARCH_TASK_STATE_SEGMENT_H_INCLUDED
