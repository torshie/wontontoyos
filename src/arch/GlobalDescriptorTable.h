#ifndef KERNEL_ARCH_GLOBAL_DESCRIPTOR_TABLE_H_INCLUDED
#define KERNEL_ARCH_GLOBAL_DESCRIPTOR_TABLE_H_INCLUDED

#include "arch/getProcessorInstance.h"
#include <generic/type.h>
#include <generic/STATIC_ASSERT.h>
#include "NullDescriptor.h"
#include "TaskStateSegment.h"
#include "CodeSegmentDescriptor.h"
#include "DataSegmentDescriptor.h"
#include "TaskStateSegmentDescriptor.h"

namespace kernel {

struct GlobalDescriptorTable {
	friend GlobalDescriptorTable& getProcessorInstance<GlobalDescriptorTable>();

	/**
	 * The order of these descriptors are important:
	 * 1. kernelData and kernelCode must have the same offset as in boot/loader.S
	 * 2. syscall & sysret are used. Refer to AMD/Intel's system programming manual for
	 * detailed information.
	 */
	NullDescriptor null;
public:
	CodeSegmentDescriptor kernelCode;
	DataSegmentDescriptor kernelData;
private:
	// XXX 32-bit user space code isn't support, so create a private dummy 32-bit Code Descriptor
	NullDescriptor code32;
public:
	DataSegmentDescriptor userData;
	CodeSegmentDescriptor userCode;
	TaskStateSegmentDescriptor taskState;

	enum {
		OFFSET_KERNEL_CODE = sizeof(NullDescriptor),
		OFFSET_KERNEL_DATA = sizeof(CodeSegmentDescriptor) + OFFSET_KERNEL_CODE,
		OFFSET_USER_DATA = sizeof(DataSegmentDescriptor) + sizeof(NullDescriptor)
							+ OFFSET_KERNEL_DATA,
		OFFSET_USER_CODE = sizeof(DataSegmentDescriptor) + OFFSET_USER_DATA,
		OFFSET_TASK_STATE = sizeof(CodeSegmentDescriptor) + OFFSET_USER_CODE
	};

private:
	GlobalDescriptorTable(const GlobalDescriptorTable&);
	const GlobalDescriptorTable& operator=(const GlobalDescriptorTable&);

	char __padding[sizeof(void*) - sizeof(U16)];
	U16 limit;
	void* base;

	GlobalDescriptorTable();

	/**
	 * Load the GDTR & TR
	 *
	 * Load the GDTR the with address of the only instance of GlobalDescriptorTable, load TR
	 * with the address of data member taskState.
	 *
	 * XXX Load TR should be placed in a separate function, maybe even in a separate class
	 */
	void load() const;
} __attribute__((packed));

inline GlobalDescriptorTable::GlobalDescriptorTable() :
		limit(sizeof(GlobalDescriptorTable) - sizeof(limit) - sizeof(base) - sizeof(__padding)),
		base(this) {
	userCode.dpl = 3;
	userData.__dpl = 3;
	load();
}

STATIC_ASSERT_EQUAL(sizeof(GlobalDescriptorTable),
		sizeof(NullDescriptor) * 2 + sizeof(DataSegmentDescriptor) * 2
		+ sizeof(CodeSegmentDescriptor) * 2
		+ sizeof(TaskStateSegmentDescriptor)
		+ sizeof(void*) - sizeof(U16) /* padding */
		+ sizeof(U16)
		+ sizeof(void*))

inline void GlobalDescriptorTable::load() const {
	Offset offsetKernelData = OFFSET_KERNEL_DATA;
	Offset offsetTaskState = OFFSET_TASK_STATE;

	asm volatile("lgdt %0\n"
			"mov %%ax, %%ds\n"
			"mov %%ax, %%ss\n"
			"mov %%ax, %%es\n"
			"mov %%ax, %%fs\n"
			"mov %%ax, %%gs\n"
			"ltr %1" : : "m"(limit), "m"(offsetTaskState), "a"(offsetKernelData));
}

} /* namespace kernel */

#endif /* KERNEL_ARCH_GLOBAL_DESCRIPTOR_TABLE_H_INCLUDED */
