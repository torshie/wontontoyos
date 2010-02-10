#include "Printer.h"
#include <generic/getSingleInstance.h>
#include <kernel/abi.h>

namespace kernel {

Printer::Printer()
		: buffer((U16*)(KERNEL_VIRTUAL_BASE + 0xb8000)),
		x(0), y(0) {
	for (int i = 0; i < 25; ++i) {
		scroll();
	}
}

Printer& Printer::printChar(char c) {
	if (c == '\r') {
		x = 0;
		return *this;
	}
	if (c == '\n') {
		x = 0;
		++y;
	} else {
		buffer[80 * y + x] = 0x0f00 | c;
		++x;
	}
	if (x >= 80) {
		x = 0;
		++y;
	}
	if (y >= 25) {
		scroll();
		y = 24;
	}
	return *this;
}

void Printer::scroll() {
	for (int i = 1; i < 25; ++i) {
		for (int j = 0; j < 80; ++j) {
			buffer[(i - 1) * 80 + j] = buffer[i * 80 + j];
		}
	}
	for (int j = 0; j < 80; ++j) {
		buffer[24 * 80 + j] = 0x0f00 | ' ';
	}
}

} /* namespace kernel */
