#include "Message.h"
#include "InterruptTable.h"
#include "GlobalDescriptorTable.h"
#include "InterruptHandler.h"
#include <generic/Utils.h>
#include <generic/type.h>

namespace kernel {

// Defined in interruptServiceRoutine.S
extern "C" Address isrTable[InterruptTable::HANDLER_COUNT];

InterruptTable::Descriptor::Descriptor() {
	Utils::memset(this, 0, sizeof(Descriptor));
	selector = GlobalDescriptorTable::OFFSET_KERNEL_CODE;
	// XXX Evil literal constants
	type = 0xe;
	present = 1;
}

InterruptTable::InterruptTable() {
	address = (U64)(this->table);
	limit = sizeof(table) - 1;

	for (int i = 0; i < HANDLER_COUNT; ++i) {
		table[i].setOffset(isrTable[i]);
	}
	Utils::memset(handler, 0, sizeof(handler));

	setHandler(PAGE_FAULT, InterruptHandler<PAGE_FAULT>::handle);
	setHandler(DOUBLE_FAULT, InterruptHandler<DOUBLE_FAULT>::handle);
	setHandler(APIC_TIMER_INTERRUPT, InterruptHandler<APIC_TIMER_INTERRUPT>::handle);

	load();
}

void InterruptTable::handle(unsigned int isrNumber) {
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

	InterruptTable& idt = getProcessorInstance<InterruptTable>();
	if (idt.handler[isrNumber] != 0) {
		idt.handler[isrNumber]();
	} else {
		if (isrNumber < (sizeof(ISR_NAME) / sizeof(char*))) {
			Message::critical << ISR_NAME[isrNumber] << "\n";
		} else {
			Message::critical << "### Unknown Interrupt: " << isrNumber << "\n";
		}
		for (;;)
			;
	}
}

} /* namespace kernel */
