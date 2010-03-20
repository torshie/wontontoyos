#ifndef KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED

#include "InterruptDescriptorTable.h"
#include "Printer.h"
#include <generic/type.h>
#include "Processor.h"

namespace kernel {

template<int INTERUPT> class InterruptHandler;

template<> class InterruptHandler<InterruptDescriptorTable::PAGE_FAULT> {
public:
	static void handle() {
		Processor& processor = getSingleInstance<Processor>();
		U64 linearAddress = processor.getRegister<Processor::CR2, U64>();
		Message::critical << "#Page Fault: accessing " << linearAddress << "\n";
		processor.halt();
	}
};

} // namespace kernel

#endif // KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
