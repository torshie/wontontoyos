#include "Message.h"
#include "InterruptDescriptorTable.h"
#include "GlobalDescriptorTable.h"
#include "InterruptHandler.h"
#include <generic/Utils.h>
#include <generic/type.h>

namespace kernel {

/**
 * Defined in interruptServiceRoutine.S
 */
extern "C" Address isrAddressTable[InterruptDescriptorTable::HANDLER_COUNT];

InterruptDescriptorTable::InterruptDescriptor::InterruptDescriptor() {
	Utils::memset(this, 0, sizeof(InterruptDescriptor));
	selector = GlobalDescriptorTable::OFFSET_KERNEL_CODE;
	// XXX Evil constants
	type = 0xe;
	present = 1;
}

InterruptDescriptorTable::InterruptDescriptorTable() {
	address = (U64)(this->table);
	limit = sizeof(table) - 1;

	for (int i = 0; i < HANDLER_COUNT; ++i) {
		table[i].setOffset(isrAddressTable[i]);
	}
	Utils::memset(handler, 0, sizeof(handler));

	setHandler(PAGE_FAULT, InterruptHandler<PAGE_FAULT>::handle);
}

void InterruptDescriptorTable::handle(int isrNumber) {
	static char const * const ISR_NAME[] = {
		"#DE Devide By Zero",
		"#DB Debug Exception",
		"NMI Exception",
		"#BP Breakpoint Exception",
		"#OF Overflow Exception",
		"#BR BOUND Range Exceeded Exception",
		"#UD Invalid Opcode Exception",
		"#NM Device Not Available Exception",
		"#DF Double Fault Exception",
		"Coprocessor Segment Overrun",
		"#TS Invalid TSS Exception",
		"#NP Segment Not Present",
		"#SS Stack Fault Exception",
		"#GP General Protection Exception",
		"#PF Page Fault Exception",
		"Reserved 15",
		"#MF X87 FPU Floating-Point Error",
		"#AC Alignment Check Exception",
		"#MC Machine-Check Exception",
		"#XM SIMD Floating-Point Exception"
	};

	InterruptDescriptorTable& idt = getSingleInstance<InterruptDescriptorTable>();
	if (idt.handler[isrNumber] != 0) {
		idt.handler[isrNumber]();
	} else {
		if (isrNumber != DOUBLE_FAULT) {
			Message::critical << ISR_NAME[isrNumber];
			for (;;)
				;
		}
	}
}

} /* namespace kernel */
