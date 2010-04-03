#ifndef KERNEL_DRIVER_TIMER_HIGH_PRECISION_EVENT_TIMER_H_INCLUDED
#define KERNEL_DRIVER_TIMER_HIGH_PRECISION_EVENT_TIMER_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>
#include "arch/InterruptController.h"

namespace kernel {

class HighPrecisionEventTimer {
	friend HighPrecisionEventTimer& getSingleInstance<HighPrecisionEventTimer>();
	HighPrecisionEventTimer() {}
	HighPrecisionEventTimer(const HighPrecisionEventTimer&);
	const HighPrecisionEventTimer& operator = (const HighPrecisionEventTimer&);

public:
	enum {
		TIME_BASE_ADDRESS = InterruptController::CONTROLLER_BASE_ADDRESS + APIC_MEMORY_SIZE
	};

	void initialize(Address address);
};

} // namespace kernel

#endif // KERNEL_DRIVER_TIMER_HIGH_PRECISION_EVENT_TIMER_H_INCLUDED
