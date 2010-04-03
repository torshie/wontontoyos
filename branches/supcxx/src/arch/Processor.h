#ifndef KERNEL_ARCH_PROCESSOR_H_INCLUDED
#define KERNEL_ARCH_PROCESSOR_H_INCLUDED

#include <generic/type.h>
#include "getProcessorInstance.h"
#include "Message.h"

namespace kernel {

class Processor {
	friend Processor& getProcessorInstance<Processor>();

	// XXX Find out why the constructor never get called
	Processor() {Message::critical << "Where is this message???\n";}

	Processor(const Processor&);
	const Processor& operator = (const Processor&);

public:
	enum Register {
		CR0, CR2, CR3, CR4
	};

	template<int REGISTER> void setRegister(NativeUnsigned value);
	template<int REGISTER> NativeUnsigned getRegister();
	U64 getModelSpecificRegister(U32 reg);
	void setModeSpecificRegister(U32 reg, U64 value);
	void halt();

	/**
	 * XXX Find out why the default constructor never get called and we need this method
	 * to initialize !!!
	 */
	void initialize();
};

} // namespace kernel

#endif // KERNEL_ARCH_PROCESSOR_H_INCLUDED
