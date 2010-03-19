#include "Processor.h"

namespace kernel {

template<> void Processor::getRegister<Processor::RSP, U64>(U64& value) const {
	asm volatile("mov %%rsp, %0" : "=m"(value));
	value += sizeof(Address);
}

template<> void Processor::getRegister<Processor::CR3, U64>(U64& value) const {
	asm volatile("mov %%cr3, %%rax\n"
			"mov %%rax, %0" : "=m"(value) : "%rax");
}

template<> void Processor::setRegister<Processor::CR3, U64>(U64 value) {
	asm volatile("mov %0, %%rax\n"
			"mov %%rax, %%cr3" : : "m"(value) : "%rax");
}

} // namespace kernel
