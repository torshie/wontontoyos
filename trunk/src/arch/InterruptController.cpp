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
		PHYSICAL_BASE_APIC = 0xFEE00000
	};

	PageMap::create(VIRTUAL_BASE_APIC, MEMORY_SIZE_APIC, PHYSICAL_BASE_APIC);
}

void InterruptController::signal() {
	Register<REG_END_OF_INTERRUPT>::set();
}

} // namespace kernel
