#include "BochsGraphicsAdaptor.h"
#include "arch/Port.h"

namespace kernel {

bool BochsGraphicsAdaptor::initialize() {
	U16 id = readRegister(REGISTER_ID);
	if (id < BGA_MIN_VERSION || id > BGA_MAX_VERSION) {
		Message::warning << "Unsupported Bochs Graphics Adaptor Version: " << id << "\n";
		return false;
	}

	disable();
	writeRegister(REGISTER_X_RESOLUTION, DEFAULT_X_RESOLUTION);
	writeRegister(REGISTER_Y_RESOLUTION, DEFAULT_Y_RESOLUTION);
	writeRegister(REGISTER_DEPTH, DEFAULT_DEPTH);
	enable();

	return true;
}

void BochsGraphicsAdaptor::writeRegister(U16 index, U16 data) {
	Port::write(INDEX_PORT, index);
	Port::write(DATA_PORT, data);
}

U16 BochsGraphicsAdaptor::readRegister(U16 index) {
	U16 data;
	Port::write(INDEX_PORT, index);
	Port::read(DATA_PORT, data);
	return data;
}

} // namespace kernel
