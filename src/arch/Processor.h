#ifndef KERNEL_ARCH_PROCESSOR_H_INCLUDED
#define KERNEL_ARCH_PROCESSOR_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class Processor {
	~Processor();
public:
	enum __ {
		CR0, CR2, CR3, CR4
	};

	template<int REGISTER> class Register;

	static U64 getModelSpecificRegister(U32 reg);
	static void setModeSpecificRegister(U32 reg, U64 value);
	static void halt();

	static void initializeUserMode();
};

#define SPECIALIZE_PROCESSOR_REGISTER(reg) \
	template<> class Processor::Register<Processor::reg> { \
	public: \
		static void set(NativeUnsigned value) { \
			asm volatile("mov %0, %%" #reg : : "r"(value)); \
	} \
	static NativeUnsigned get() { \
		NativeUnsigned ret; \
		asm volatile("mov %%" #reg ", %0" : "=r"(ret)); \
		return ret; \
	} \
};

SPECIALIZE_PROCESSOR_REGISTER(CR0)
SPECIALIZE_PROCESSOR_REGISTER(CR2)
SPECIALIZE_PROCESSOR_REGISTER(CR3)
SPECIALIZE_PROCESSOR_REGISTER(CR4)

#undef SPECIALIZE_PROCESSOR_REGISTER

} // namespace kernel

#endif // KERNEL_ARCH_PROCESSOR_H_INCLUDED
