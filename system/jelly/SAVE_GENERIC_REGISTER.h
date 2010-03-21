#ifndef JELLY_SAVE_GENERIC_REGISTER_H_INCLUDED
#define JELLY_SAVE_GENERIC_REGISTER_H_INCLUDED

#ifdef SAVE_GENERIC_REGISTER
#	error "SAVE_GENERIC_REGISTER is already defined"
#else
// XXX Optimize, no need to save this many registers */
#define SAVE_GENERIC_REGISTER \
	"push %%rax\n" \
	"push %%rbx\n" \
	"push %%rcx\n" \
	"push %%rdx\n" \
	"push %%rsi\n" \
	"push %%rdi\n" \
	"push %%rbp\n" \
	"push %%r8\n" \
	"push %%r9\n" \
	"push %%r10\n" \
	"push %%r11\n" \
	"push %%r12\n" \
	"push %%r13\n" \
	"push %%r14\n" \
	"push %%r15\n"
#endif // #ifdef SAVE_GENERIC_REGISTER

#endif // JELLY_SAVE_GENERIC_REGISTER_H_INCLUDED
