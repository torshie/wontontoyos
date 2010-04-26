#ifndef KERNEL_DRIVER_TIMER_REAL_TIME_CLOCK_H_INCLUDED
#define KERNEL_DRIVER_TIMER_REAL_TIME_CLOCK_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>

namespace kernel {

class RealTimeClock {
	enum {
		INDEX_PORT = 0x70,
		DATA_PORT = 0x71
	};

	friend RealTimeClock& getSingleInstance<RealTimeClock>();
	RealTimeClock();

public:
	void writeRegister(U8 reg, U8 data);
	U8 readRegister(U8 reg);
};

} // namespace kernel

#endif // KERNEL_DRIVER_TIMER_REAL_TIME_CLOCK_H_INCLUDED
