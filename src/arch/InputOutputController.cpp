#include "InputOutputController.h"
#include "Message.h"
#include "mm/PageMap.h"

namespace kernel {

InputOutputController::InputOutputController() {
	enum {
		PHYSICAL_BASE_IOAPIC = 0xFEC00000
	};
	PageMap::create(VIRTUAL_BASE_IOAPIC, MEMORY_SIZE_IOAPIC, PHYSICAL_BASE_IOAPIC);
}

void InputOutputController::setRegister(U32 reg, U32 value) {
	volatile U32* selector = (volatile U32*)OFFSET_SELECTOR;
	volatile U32* window = (volatile U32*)OFFSET_WINDOW;

	*selector = reg;
	*window = value;
}

void InputOutputController::setRouter(int index, Router router) {
	enum {
		ROUTER_ENTRY_BASE = 0x10
	};
	setRegister(ROUTER_ENTRY_BASE + index * 2, (U32)router.__value);
	setRegister(ROUTER_ENTRY_BASE + index * 2 + 1, (U32)(router.__value >> 32));
}

U32 InputOutputController::getRegister(U32 reg) {
	volatile U32* selector = (volatile U32*)OFFSET_SELECTOR;
	volatile U32* window = (volatile U32*)OFFSET_WINDOW;
	*selector = reg;
	return *window;
}

} // namespace kernel
