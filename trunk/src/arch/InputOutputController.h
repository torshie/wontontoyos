#ifndef KERNEL_ARCH_INPUT_OUTPUT_CONTROLLER_H_INCLUDED
#define KERNEL_ARCH_INPUT_OUTPUT_CONTROLLER_H_INCLUDED

#include <generic/getSingleInstance.h>
#include <generic/type.h>
#include <kernel/abi.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

class InputOutputController {
	friend InputOutputController& getSingleInstance<InputOutputController>();
	InputOutputController();
	InputOutputController(const InputOutputController&);
	const InputOutputController& operator = (const InputOutputController&);
public:
	enum {
		REG_ID = 0,
		REG_VERSION = 1,
		REG_ARBITRATION = 2,

		// XXX This value should be detected at runtime.
		ROUTER_HPET_TIMER = 4,
	};

	union Router {
		U64 __value;
		struct {
			U8 interrupt;
			U8 deliveryMode:3;
			U8 logicalMode:1;
			U8 deliveryStatus:1;
			U8 lowActive:1;
			U8 __ignored:1;
			U8 levelTrigger:1;
			U8 mask:1;
			U64 __reserved:39;
			U8 desination;
		} __attribute__((packed));

		explicit Router(U8 interruptVector) : __value(0), interrupt(interruptVector) {}
	};

	void setRegister(U32 reg, U32 value);
	U32 getRegister(U32 reg);
	void setRouter(int index, Router router);

private:
	enum {
		OFFSET_SELECTOR = VIRTUAL_BASE_IOAPIC + 0,
		OFFSET_WINDOW = VIRTUAL_BASE_IOAPIC + 0x10
	};
};

STATIC_ASSERT_EQUAL(sizeof(InputOutputController::Router), 8);

} // namespace kernel

#endif // KERNEL_ARCH_INPUT_OUTPUT_CONTROLLER_H_INCLUDED
