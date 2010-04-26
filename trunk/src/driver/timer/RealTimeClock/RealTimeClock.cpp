#include "RealTimeClock.h"
#include "arch/Port.h"

namespace kernel {

RealTimeClock::RealTimeClock() {
	U8 b = readRegister(0xB);
	writeRegister(0xB, b | 0x40);
	readRegister(0xC);
}

U8 RealTimeClock::readRegister(U8 reg) {
	Port::write(INDEX_PORT, reg);
	U8 data;
	Port::read(DATA_PORT, data);
	return data;
}

void RealTimeClock::writeRegister(U8 reg, U8 data) {
	Port::write(INDEX_PORT, reg);
	Port::write(DATA_PORT, data);
}

} // namespace kernel
