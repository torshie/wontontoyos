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
		CR2, CR3
	};

	template<int REGISTER, typename Integer> void setRegister(Integer value);
	template<int REGISTER, typename Integer> Integer getRegister();
	void enterUserMode(Address entry);
	U64 getModelSpecificRegister(U32 reg);
	void setModeSpecificRegister(U32 reg, U64 value);
	void halt();
	void initialize(); // XXX Find out why we cannot put initialization code into constructor
};

} // namespace kernel

#endif // KERNEL_ARCH_PROCESSOR_H_INCLUDED
