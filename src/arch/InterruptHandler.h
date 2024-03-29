#ifndef KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED

#include "InterruptTable.h"
#include "Printer.h"
#include <generic/type.h>
#include "Processor.h"
#include "Message.h"
#include "InterruptController.h"
#include "driver/timer/RealTimeClock/RealTimeClock.h"

namespace kernel {

template<int INTERUPT> class InterruptHandler;

template<> class InterruptHandler<InterruptTable::HANDLER_PAGE_FAULT> {
public:
	static void handle() {
		NativeUnsigned linearAddress = Processor::Register<Processor::CR2>::get();
		Message::critical << "#Page Fault: accessing " << linearAddress << "\n";
		Processor::halt();
	}
};

template<> class InterruptHandler<InterruptTable::HANDLER_DOUBLE_FAULT> {
public:
	static void handle() {
		Message::brief << "#Double Fault\n";
	}
};

template<> class InterruptHandler<InterruptTable::HANDLER_HPET_TIMER> {
public:
	static void handle() {
		static int tick = 0;
		++tick;
	}
};

template<> class InterruptHandler<InterruptTable::HANDLER_IRQ8> {
public:
	static void handle() {
		static int tick = 0;
		++tick;
		Message::brief << "RTC tick: " << tick << "C register: "
				<< getSingleInstance<RealTimeClock>().readRegister(0xC) << "\n";
	}
};

} // namespace kernel

#endif // KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
