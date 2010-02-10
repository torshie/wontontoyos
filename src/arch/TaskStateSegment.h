#ifndef KERNEL_ARCH_TASK_STATE_SEGMENT_H_INCLUDED
#define KERNEL_ARCH_TASK_STATE_SEGMENT_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>
#include <generic/Memory.h>

namespace kernel {

/**
 * Task State Segment
 *
 * Referer to AMD/Intel's system programming manual for more detailed information
 */
struct TaskStateSegment {
	friend TaskStateSegment& getSingleInstance<TaskStateSegment>();
private:
	U32 reserved0;
public:
	U64 rsp[3];
	U64 ist[7]; /* IST0 is reserved */
private:
	U64 reserved1;
	U16 reserved2;
public:
	U16 ioMapBase;
	U8 ioMap[8192];

private:
	TaskStateSegment() {
		Memory::zeroize(this, sizeof(TaskStateSegment) - sizeof(ioMap));
		Memory::memset(ioMap, 0xff, sizeof(ioMap));
		ioMapBase = (char*)&ioMapBase - (char*)this;
	}

	TaskStateSegment(const TaskStateSegment&);
	const TaskStateSegment& operator = (const TaskStateSegment&);

} __attribute__((packed));

} /* namespace kernel */

#endif /* KERNEL_ARCH_TASK_STATE_SEGMENT_H_INCLUDED */
