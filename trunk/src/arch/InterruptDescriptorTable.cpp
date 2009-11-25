#include "../Printer.h"
#include "InterruptDescriptorTable.h"
#include <base/Memory.h>

using namespace base;

namespace kernel {

/**
 * Defined in interruptServiceRoutine.S
 */
extern "C" Address
		isrAddressTable[InterruptDescriptorTable::HANDLER_COUNT];

InterruptDescriptorTable::InterruptDescriptor::InterruptDescriptor() {
	base::Memory::memset(this, 0, sizeof(InterruptDescriptor));
	//selector = GlobalDescriptorTable::OFFSET_KERNEL_CODE;
	/**
	 * XXX Find out why the linked binary is wrong when we use
	 * selector = GlobalDescriptorTable
	 */
	selector = 8;
	type = 0xe;
	present = 1;
}

InterruptDescriptorTable::InterruptDescriptorTable() {
	address = (U64)(this->table);
	limit = sizeof(table) - 1;

	for (int i = 0; i < HANDLER_COUNT; ++i) {
		table[i].setOffset(isrAddressTable[i]);
	}
	base::Memory::memset(handler, 0, sizeof(handler));

	setHandler(PAGE_FAULT, 0);
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
	Printer& console = base::getSingleInstance<Printer>();
	console << ISR_NAME[isrNumber];

	InterruptDescriptorTable& idt
			= getSingleInstance<InterruptDescriptorTable>();
	if (idt.handler[isrNumber] != 0) {
		idt.handler[isrNumber]();
	}

		for (;;)
			;
}

} /* namespace kernel */
