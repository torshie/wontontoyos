#ifndef KERNEL_ARCH_PORT_H_INCLUDED
#define KERNEL_ARCH_PORT_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class Port {
public:
	static void write(U16 port, U8 data) {
		asm volatile ("out %%al,%%dx" : : "d"(port), "a"(data));
	}

	static void write(U16 port, U16 data) {
		asm volatile ("out %%ax,%%dx" : : "d"(port), "a"(data));
	}

	static void write(U16 port, U32 data) {
		asm volatile ("out %%eax,%%dx" : : "d"(port), "a"(data));
	}

	static void read(U16 port, U8& data) {
		asm volatile ("in %%dx,%%al" : "=a"(data) : "d"(port));
	}

	static void read(U16 port, U16& data) {
		asm volatile ("in %%dx,%%ax" : "=a"(data) : "d"(port));
	}

	static void read(U16 port, U32& data) {
		asm volatile ("in %%dx,%%eax" : "=a"(data) : "d"(port));
	}
};

} // namespace kernel

#endif // KERNEL_ARCH_PORT_H_INCLUDED
