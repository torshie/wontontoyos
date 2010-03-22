#include "Message.h"
#include "InterruptDescriptorTable.h"
#include "GlobalDescriptorTable.h"
#include "InterruptHandler.h"
#include <generic/Utils.h>
#include <generic/type.h>

namespace kernel {

// Defined in interruptServiceRoutine.S
extern "C" Address isrTable[InterruptDescriptorTable::HANDLER_COUNT];

InterruptDescriptorTable::Descriptor::Descriptor() {
	Utils::memset(this, 0, sizeof(Descriptor));
	selector = GlobalDescriptorTable::OFFSET_KERNEL_CODE;
	// XXX Evil literal constants
	type = 0xe;
	present = 1;
}

InterruptDescriptorTable::InterruptDescriptorTable() {
	address = (U64)(this->table);
	limit = sizeof(table) - 1;

	for (int i = 0; i < HANDLER_COUNT; ++i) {
		table[i].setOffset(isrTable[i]);
	}
	Utils::memset(handler, 0, sizeof(handler));

	setHandler(PAGE_FAULT, InterruptHandler<PAGE_FAULT>::handle);
	setHandler(DOUBLE_FAULT, InterruptHandler<DOUBLE_FAULT>::handle);
}

void InterruptDescriptorTable::handle(unsigned int isrNumber) {
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
		if (isrNumber < (sizeof(ISR_NAME) / sizeof(char*))) {
			Message::critical << ISR_NAME[isrNumber] << "\n";
		} else {
			Message::critical << "#Interrupt: " << isrNumber << "\n";
		}
	}
}

} /* namespace kernel */
