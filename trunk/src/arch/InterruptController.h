#ifndef KERNE_ARCH_INTERRUPT_CONTROLLER_H_INCLUDED
#define KERNE_ARCH_INTERRUPT_CONTROLLER_H_INCLUDED

#include "getProcessorInstance.h"
#include <generic/type.h>
#include <kernel/abi.h>
#include "X64Constant.h"
#include <cxx/BUG.h>

namespace kernel {

class InterruptController {
	friend class InterruptController& getProcessorInstance<InterruptController>();
	InterruptController();
	InterruptController(const InterruptController&);
	const InterruptController& operator = (const InterruptController&);

	template<int REGISTER> class Register;

public:
	enum {
		CONTROLLER_BASE_ADDRESS = KERNEL_VIRTUAL_BASE + KERNEL_RESERVED_MEMORY
	};

	// XXX This is ugly
	static void endInterrupt();
};

#ifndef SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER
#	define NULL_GETTER(reg, Type)
#	define NULL_SETTTER(reg, Type)
#	define DEFAULT_GETTER(reg, Type) \
	static Type get() { \
		return *(Type*)(InterruptController::CONTROLLER_BASE_ADDRESS + reg); \
	}
#	define DEFAULT_SETTER(reg, Type) \
		static void set(Type value) { \
			*(Type*)(InterruptController::CONTROLLER_BASE_ADDRESS + reg) = value; \
		}

#	define SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(reg, Type, Getter, Setter) \
		template<> class InterruptController::Register<reg> { \
		public: \
			Getter(reg, Type) \
			Setter(reg, Type) \
		}
#else
#error "SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER is already defined"
#endif

SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(APIC_REGISTER_ID, U32,
		DEFAULT_GETTER, DEFAULT_SETTER);
SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(APIC_REGISTER_VERSION, U32,
		DEFAULT_GETTER, DEFAULT_SETTER);
SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(APIC_REGISTER_TIMER_INITIAL_COUNT, U32,
		DEFAULT_GETTER, DEFAULT_SETTER);
SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(APIC_REGISTER_ENTRY_TIMER, U32,
		DEFAULT_GETTER, DEFAULT_SETTER);
SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(APIC_REGISTER_TIMER_DIVIDE_CONFIGURATION, U32,
		DEFAULT_GETTER, DEFAULT_SETTER);
SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(APIC_REGISTER_END_OF_INTERRUPT, U32,
		NULL_GETTER, DEFAULT_SETTER);

#undef SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER

} // namespace kernel

#endif // KERNE_ARCH_INTERRUPT_CONTROLLER_H_INCLUDED
