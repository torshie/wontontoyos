#include "Printer.h"
#include <generic/getSingleInstance.h>

#define DEBUG(a) \
	do { \
		::kernel::getSingleInstance< ::kernel::Printer>() << #a << ": " << (a) << "\n"; \
		for (;;); \
	} while (0)
