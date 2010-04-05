#include "arch/Processor.h"
#include "arch/X64Constant.h"
#include "createPageMap.h"
#include "Message.h"
#include "InterfaceDescriptionPointer.h"
#include "InterfaceDescriptionTable.h"
#include "EventTimerDescriptor.h"
#include <cxx/initCxxSupport.h>
#include <cxx/new.h>

using namespace kernel;

namespace pangu {

extern "C" Address loadFileImage(void*, Size);
extern "C" char kernelStart, kernelEnd, loaderStart, loaderEnd, globalDescriptorTablePointer;
extern "C" Address rise() {
	initCxxSupport();

	const InterfaceDescriptionPointer* pointer = InterfaceDescriptionPointer::find();
	const InterfaceDescriptionTable* root = pointer->getRootTable();
	const InterfaceDescriptionTable* hpet = root->find("HPET");
	if (hpet == 0) {
		Message::fatal << "Cannot find HPET\n";
		for (;;);
	}

	EventTimerDescriptor* timer = (EventTimerDescriptor*)(&(hpet->data));

	PagePointer<4>* map = createPageMap();
	Address loaderEntry = loadFileImage(&loaderStart, &loaderEnd - &loaderStart);
	// XXX Evil literal
	*(U64*)(loaderEntry - 32) = timer->address; // Pass parameter to 64-bit loader

	Processor::Register<Processor::CR0>::set(1 << CR0_BIT_PROTECTION_ENABLED);
	Processor::Register<Processor::CR4>::set(
			(1 << CR4_BIT_PHYSICAL_ADDRESS_EXTENSION)
				| (1 << CR4_BIT_PAGE_GLOBAL_ENABLE)
				| (1 << CR4_BIT_OS_FXSAVE_FXRSTOR_SUPPORT));
	Processor::Register<Processor::CR3>::set((NativeUnsigned)map);
	Processor::setModeSpecificRegister(MSR_EXTENDED_FEATURE_ENABLE_REGISTER,
			(1 << EFER_BIT_NO_EXECUTE_ENABLE)
				| (1 << EFER_BIT_LONG_MODE_ENABLE)
				| (1 << EFER_BIT_SYSTEM_CALL_EXTENSION));
	asm volatile("lgdt %0" : : "m"(globalDescriptorTablePointer));
	NativeUnsigned cr0 = Processor::Register<Processor::CR0>::get();
	Processor::Register<Processor::CR0>::set(cr0 | (1 << CR0_BIT_PAGING));

	return loaderEntry;
}

} // namespace pangu
