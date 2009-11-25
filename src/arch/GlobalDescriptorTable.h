#ifndef __WONTON_KERNEL_GLOBAL_DESCRIPTOR_TABLE_H_INCLUDED__
#define __WONTON_KERNEL_GLOBAL_DESCRIPTOR_TABLE_H_INCLUDED__

#include <base/getSingleInstance.h>
#include <base/type.h>
#include "NullDescriptor.h"
#include "TaskStateSegment.h"
#include "CodeSegmentDescriptor.h"
#include "DataSegmentDescriptor.h"
#include "TaskStateSegmentDescriptor.h"

namespace kernel {

/**
 * Global Descriptor Table
 *
 * See AMD/Intel's system programming manual for more detailed
 * information
 */
struct GlobalDescriptorTable {
	friend GlobalDescriptorTable&
			base::getSingleInstance<GlobalDescriptorTable>();

	/**
	 * The order of these descriptors are important:
	 * 1. kernelData and kernelCode must
	 *    have the same offset as in src/boot.S
	 * 2. Data Segment Descriptor must be just before Code Segment
	 *    Descriptor, since we use syscall and sysret. See system
	 *    programming manual for more detailed information
	 */
	NullDescriptor null;
	DataSegmentDescriptor kernelData;
	CodeSegmentDescriptor kernelCode;
	DataSegmentDescriptor userData;
	CodeSegmentDescriptor userCode;
	TaskStateSegmentDescriptor taskState;

	enum {
		OFFSET_KERNEL_DATA = sizeof(NullDescriptor),
		OFFSET_KERNEL_CODE = sizeof(DataSegmentDescriptor)
								+ OFFSET_KERNEL_DATA,
		OFFSET_USER_DATA = sizeof(CodeSegmentDescriptor)
								+ OFFSET_KERNEL_CODE,
		OFFSET_USER_CODE = sizeof(DataSegmentDescriptor)
								+ OFFSET_USER_DATA,
		OFFSET_TASK_STATE = sizeof(CodeSegmentDescriptor)
								+ OFFSET_USER_CODE
	};

private:
	char _pad[6];
	base::U16 limit;
	void* base;

	GlobalDescriptorTable()
			: limit(sizeof(null) + sizeof(kernelData)
					+ sizeof(kernelCode) + sizeof(userData)
					+ sizeof(userCode) + sizeof(taskState) - 1),
			base(this) {
		userCode.dpl = 3;
		userData._dpl = 3;
	}
	GlobalDescriptorTable(const GlobalDescriptorTable&);
	const GlobalDescriptorTable& operator=(const GlobalDescriptorTable&);

public:

	/**
	 * Load the GDTR & TR
	 *
	 * Load the GDTR the with address of the only instance of
	 * GlobalDescriptorTable, load TR with the address of data member
	 * taskState.
	 *
	 * XXX Load TR should be placed in a separate function, maybe even
	 * in a separate class
	 */
	void load() const;
};

namespace internal {
/**
 * Make sure GlobalDescriptorTable is correctly padded
 */
void __checkStructureSize(char check
		[sizeof(GlobalDescriptorTable)
			 == sizeof(NullDescriptor)
				+ sizeof(DataSegmentDescriptor) * 2
				+ sizeof(CodeSegmentDescriptor) * 2
				+ sizeof(TaskStateSegmentDescriptor)
				+ 6
				+ sizeof(base::U16)
				+ sizeof(void*) ? 1 : -1]);
}

inline void GlobalDescriptorTable::load() const {
	asm volatile("lgdt %0" : : "m"(limit));

	base::Offset offsetKernelData = OFFSET_KERNEL_DATA;
	base::Offset offsetTaskState = OFFSET_TASK_STATE;

	asm volatile("mov %0, %%rax\n"
			"mov %%ax, %%ds\n"
			"mov %%ax, %%ss\n"
			"mov %%ax, %%es\n"
			"mov %%ax, %%fs\n"
			"mov %%ax, %%gs\n" : :"m"(offsetKernelData));
	asm volatile("ltr %0" : : "m"(offsetTaskState));
}

} /* namespace kernel */

#endif
