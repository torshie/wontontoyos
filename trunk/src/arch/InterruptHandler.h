#ifndef KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED

#include "InterruptDescriptorTable.h"
#include <generic/type.h>

namespace kernel {

template<int INTERUPT>
class InterruptHandler;

template<>
class InterruptHandler<InterruptDescriptorTable::PAGE_FAULT> {
public:
	static void handle() {
		U64 linearAddress = readCR2();
		Printer& console = getSingleInstance<Printer>();
		console << "#Page Fault: accessing " << linearAddress << "\n";

		for (;;)
			;
	}

private:
	static U64 readCR2() {
		U64 result;
		asm volatile("mov %%cr2, %0" : "=r"(result));
		return result;
	}
};

} /* kernel */

#endif /* KERNEL_ARCH_INTERRUPT_HANDLER_H_INCLUDED */
