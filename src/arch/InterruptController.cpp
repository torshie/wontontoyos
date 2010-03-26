#include "InterruptController.h"
#include "Message.h"
#include "Processor.h"
#include "X64Constant.h"
#include "mm/PageMap.h"
#include "mm/PageTable.h"
#include "InterruptDescriptorTable.h"

namespace kernel {

InterruptController::InterruptController() {
	Processor& processor = getProcessorInstance<Processor>();
	Address physical = processor.getModelSpecificRegister(MSR_APIC_BASE_ADDRES_REGISTER);
	physical = (physical >> 12) << 12;
	PageMap::create(CONTROLLER_BASE_ADDRESS, APIC_MEMORY_SIZE, physical);
	Message::brief << "APIC ID: " << Register<APIC_REGISTER_ID>::get() << "\n";
	Message::brief << "APIC Version: " << Register<APIC_REGISTER_VERSION>::get() << "\n";
	Register<APIC_REGISTER_TIMER_DIVIDE_CONFIGURATION>::set(10);
	Register<APIC_REGISTER_TIMER_INITIAL_COUNT>::set(0x5fffff);
	Register<APIC_REGISTER_ENTRY_TIMER>::set(
			InterruptDescriptorTable::APIC_INTERRUPT_TIMER | (1 << 17));
}

void InterruptController::endInterrupt() {
	Register<APIC_REGISTER_END_OF_INTERRUPT>::set(0);
}

} // namespace kernel
