#include "Printer.h"
#include <generic/getSingleInstance.h>
#include <kernel/abi.h>

namespace kernel {

Printer::Printer()
		: buffer((U16*)(KERNEL_VIRTUAL_BASE + 0xb8000)),
		x(0), y(0) {
	for (int i = 0; i < HEIGHT; ++i) {
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
		buffer[WIDTH * y + x] = COLOR | c;
		++x;
	}
	if (x >= WIDTH) {
		x = 0;
		++y;
	}
	if (y >= HEIGHT) {
		scroll();
		y = HEIGHT - 1;
	}
	return *this;
}

void Printer::scroll() {
	for (int i = 1; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			buffer[(i - 1) * WIDTH + j] = buffer[i * WIDTH + j];
		}
	}
	for (int j = 0; j < WIDTH; ++j) {
		buffer[(HEIGHT - 1) * WIDTH + j] = COLOR | ' ';
	}
}

} /* namespace kernel */
