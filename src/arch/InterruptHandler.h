#ifndef KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED

#include "InterruptTable.h"
#include "Printer.h"
#include <generic/type.h>
#include "Processor.h"
#include "Message.h"
#include "InterruptController.h"

namespace kernel {

template<int INTERUPT> class InterruptHandler;

template<> class InterruptHandler<InterruptTable::PAGE_FAULT> {
public:
	static void handle() {
		Processor& processor = getProcessorInstance<Processor>();
		U64 linearAddress = processor.getRegister<Processor::CR2, U64>();
		Message::critical << "#Page Fault: accessing " << linearAddress << "\n";
		processor.halt();
	}
};

template<> class InterruptHandler<InterruptTable::DOUBLE_FAULT> {
public:
	static void handle() {
		Message::brief << "#Double Fault\n";
	}
};

template<> class InterruptHandler<InterruptTable::APIC_TIMER_INTERRUPT> {
public:
	static void handle() {
		static I64 tick = 1;
		Message::brief << "APIC Tick: " <<  tick << "\n";
		++tick;
		InterruptController::signal();
	}
};

} // namespace kernel

#endif // KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
