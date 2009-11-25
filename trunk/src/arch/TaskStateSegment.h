#ifndef __WONTON_KERNEL_TASK_STATE_SEGMENT_H_INCLUDED__
#define __WONTON_KERNEL_TASK_STATE_SEGMENT_H_INCLUDED__

#include <base/type.h>
#include <base/getSingleInstance.h>
#include <base/Memory.h>

namespace kernel {

/**
 * Task State Segment
 *
 * See AMD/Intel's system programming manual for more detailed
 * information
 */
struct TaskStateSegment {
	friend TaskStateSegment& base::getSingleInstance<TaskStateSegment>();
private:
	base::U32 reserved0;
public:
	base::U64 rsp[3];
	base::U64 ist[7]; /* IST0 is reserved */
private:
	base::U64 reserved1;
	base::U16 reserved2;
public:
	base::U16 ioMapBase;
	base::U8 ioMap[8192];

private:
	TaskStateSegment() {
		base::Memory::zeroize(this,
				sizeof(TaskStateSegment) - sizeof(ioMap));
		base::Memory::memset(ioMap, 0xff, sizeof(ioMap));
		ioMapBase = (char*)&ioMapBase - (char*)this;
	}

	TaskStateSegment(const TaskStateSegment&);
	const TaskStateSegment& operator = (const TaskStateSegment&);

} __attribute__((packed));

}

#endif
