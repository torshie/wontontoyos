#ifndef KERNEL_DRIVER_BOCHS_GRAPHICS_ADAPTOR_H_INCLUDED
#define KERNEL_DRIVER_BOCHS_GRAPHICS_ADAPTOR_H_INCLUDED

#include "Message.h"
#include <generic/getSingleInstance.h>

namespace kernel {

class BochsGraphicsAdaptor {
	friend BochsGraphicsAdaptor& getSingleInstance<BochsGraphicsAdaptor>();
	BochsGraphicsAdaptor() {}
	BochsGraphicsAdaptor(const BochsGraphicsAdaptor&);
	const BochsGraphicsAdaptor& operator = (const BochsGraphicsAdaptor&);

public:
	bool initialize();

	void disable() {
		writeRegister(REGISTER_ENABLE, 0);
	}

	void enable() {
		writeRegister(REGISTER_ENABLE, 1);
	}

	U16 getWidth() const {
		return DEFAULT_X_RESOLUTION;
	}

	U16 getHeight() const {
		return DEFAULT_Y_RESOLUTION;
	}

	U16 getDepth() const {
		return DEFAULT_DEPTH;
	}

private:
	enum {
		INDEX_PORT = 0x01CE,
		DATA_PORT = 0x01CF,
		BGA_MIN_VERSION = 0xB0C2,
		BGA_MAX_VERSION = 0xB0C5,

		REGISTER_ID = 0,
		REGISTER_X_RESOLUTION,
		REGISTER_Y_RESOLUTION,
		REGISTER_DEPTH,
		REGISTER_ENABLE,
		REGISTER_BANK,
		REGISTER_WIDTH,
		REGISTER_HEIGHT,
		REGISTER_X_OFFSET,
		REGISTER_Y_OFFSET,

		DEFAULT_X_RESOLUTION = 1024,
		DEFAULT_Y_RESOLUTION = 640,
		DEFAULT_DEPTH = 32
	};

	U16 readRegister(U16 index);
	void writeRegister(U16 index, U16 data);
};

} // namespace kernel

#endif // KERNEL_DRIVER_BOCHS_GRAPHICS_ADAPTOR_H_INCLUDED
