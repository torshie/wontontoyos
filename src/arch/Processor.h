#ifndef KERNEL_ARCH_PROCESSOR_H_INCLUDED
#define KERNEL_ARCH_PROCESSOR_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>

namespace kernel {

class Processor {
	friend Processor& getSingleInstance<Processor>();

	Processor() {}
	Processor(const Processor&);
	const Processor& operator = (const Processor&);

public:
	enum Register {
		RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP,
		CR0, CR1, CR2, CR3
	};

	template<int REGISTER, typename Integer> void setRegister(Integer value);
	template<int REGISTER, typename Integer> void getRegister(Integer& value) const;
};

} // namespace kernel

#endif // KERNEL_ARCH_PROCESSOR_H_INCLUDED
