#ifndef KERNE_ARCH_INTERRUPT_CONTROLLER_H_INCLUDED
#define KERNE_ARCH_INTERRUPT_CONTROLLER_H_INCLUDED

#include "getProcessorInstance.h"
#include <generic/type.h>
#include <kernel/abi.h>
#include "X64Constant.h"
#include <cxx/BUG.h>

namespace kernel {

class InterruptController {
	friend class InterruptController
			& getProcessorInstance<InterruptController> ();
	InterruptController();
	InterruptController(const InterruptController&);
	const InterruptController& operator =(const InterruptController&);

	template<int REGISTER> class Register;

public:
	enum {
		REG_ID = 0x20,
		REG_VERSION = 0x30,
		REG_TASK_PRIORITY = 0x80,
		REG_ARBITRATION_PRIORITY = 0x90,
		REG_PROCESSOR_PRIORITY = 0xA0,
		REG_END_OF_INTERRUPT = 0xB0,
		REG_REMOTE_READ = 0xC0,
		REG_LOGICAL_DESITINATION = 0xD0,
		REG_DESITINATION_FORMAT = 0xE0,
		REG_SPURIOUS_INTERRUPT_VECTOR = 0xF0,
		REG_ERROR_STATUS = 0x280,
		REG_INTERRUPT_COMMAND_LOW = 0x300,
		REG_INTERRUPT_COMMAND_HIGH = 0x310,
		REG_ENTRY_TIMER = 0x320,
		REG_ENTRY_THERMAL = 0x330,
		REG_ENTRY_PERFORMANCE_COUNTER = 0x340,
		REG_ENTRY_LINT0 = 0x350,
		REG_ENTRY_LINT1 = 0x360,
		REG_ENTRY_ERROR = 0x370,
		REG_TIMER_INITIAL_COUNT = 0x380,
		REG_TIMER_CURRENT_COUNT = 0x390,
		REG_TIMER_DIVIDE_CONFIG = 0x3E0,
		REG_EXTENDED_APIC_FEATURE = 0x400,
		REG_EXTENDED_APIC_CONTROL = 0x410,
		REG_SPECIFIC_END_OF_INTERRUPT = 0x420
	};

	// XXX This is ugly
	static void signal();
};

#define NULL_GETTER(reg, Type)
#define NULL_SETTER(reg, Type)
#define DEFAULT_GETTER(reg, Type) \
	static Type get() { \
		return *(Type*)(VIRTUAL_BASE_APIC + reg); \
	}

#define DEFAULT_SETTER(reg, Type) \
	static void set(Type value) { \
		*(Type*)(VIRTUAL_BASE_APIC + reg) = value; \
	}

#define ZERO_SETTER(reg, Type) \
	static void set() { \
		*(Type*)(VIRTUAL_BASE_APIC + reg) = 0; \
	}

#define SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(reg, Type, Getter, Setter) \
	template<> class InterruptController::Register<InterruptController::reg> { \
	public: \
		Getter(reg, Type) \
		Setter(reg, Type) \
	}

SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER(REG_END_OF_INTERRUPT, U32, NULL_GETTER, ZERO_SETTER);

#undef SPECIALIZE_INTERRUPT_CONTROLLER_REGISTER
#undef NULL_GETTER
#undef NULL_SETTER
#undef ZERO_SETTER
#undef DEFAULT_SETTER
#undef DEFAULT_GETTER

} // namespace kernel

#endif // KERNE_ARCH_INTERRUPT_CONTROLLER_H_INCLUDED
