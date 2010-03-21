#ifndef JELLY_LOAD_GENERIC_REGISTER_H_INCLUDED
#define JELLY_LOAD_GENERIC_REGISTER_H_INCLUDED

#ifdef LOAD_GENERIC_REGISTER
#	error "LOAD_GENERIC_REGISTER is already defined"
#else
// XXX Optimize, no need to save this many registers
#define LOAD_GENERIC_REGISTER \
	"pop %%r15\n" \
	"pop %%r14\n" \
	"pop %%r13\n" \
	"pop %%r12\n" \
	"pop %%r11\n" \
	"pop %%r10\n" \
	"pop %%r9\n" \
	"pop %%r8\n" \
	"pop %%rbp\n" \
	"pop %%rdi\n" \
	"pop %%rsi\n" \
	"pop %%rdx\n" \
	"pop %%rcx\n" \
	"pop %%rbx\n" \
	"pop %%rax\n"
#endif // #ifdef LOAD_GENERIC_REGISTER

#endif // JELLY_LOAD_GENERIC_REGISTER_H_INCLUDED
