#ifndef KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED

#include "InterruptDescriptorTable.h"
#include "Printer.h"
#include "System.h"
#include <generic/type.h>

namespace kernel {

template<int INTERUPT> class InterruptHandler;

template<> class InterruptHandler<InterruptDescriptorTable::PAGE_FAULT> {
public:
	static void handle() {
		U64 linearAddress = getControlRegister2();
		Printer& console = getSingleInstance<Printer>();
		console << "#Page Fault: accessing " << linearAddress << "\n";

		System::halt();
	}

private:
	static U64 getControlRegister2() {
		U64 result;
		asm volatile("mov %%cr2, %0" : "=r"(result));
		return result;
	}
};

} /* kernel */

#endif /* KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED */
