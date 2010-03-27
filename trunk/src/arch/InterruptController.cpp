#include "InterruptController.h"
#include "Message.h"
#include "Processor.h"
#include "X64Constant.h"
#include "mm/PageMap.h"
#include "mm/PageTable.h"
#include "Port.h"
#include "InterruptTable.h"

namespace kernel {

InterruptController::InterruptController() {
	enum {
		APIC_INITIAL_COUNT = 0x1000000,
		IO_APIC_BASE = 0xFEC00000,
		IO_APIC_MEMORY_SIZE = 0x1000,
		APIC_MEMORY_SIZE = 0x1000
	};

	Processor& processor = getProcessorInstance<Processor>();
	Address physical = processor.getModelSpecificRegister(MSR_APIC_BASE_ADDRES_REGISTER);
	physical = (physical >> 12) << 12;
	PageMap::create(CONTROLLER_BASE_ADDRESS, APIC_MEMORY_SIZE, physical);
	PageMap::create(CONTROLLER_BASE_ADDRESS + APIC_MEMORY_SIZE, IO_APIC_MEMORY_SIZE,
			IO_APIC_BASE);
}

void InterruptController::signal() {
	Register<APIC_REGISTER_END_OF_INTERRUPT>::set();
}

} // namespace kernel
