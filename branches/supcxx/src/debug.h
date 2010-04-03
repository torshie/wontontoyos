#include "Message.h"
#include <generic/getSingleInstance.h>

#define DEBUG(a) \
	do { \
		::kernel::Message::debug << #a << ": " << (a) << "\n"; \
		for (;;); \
	} while (0)
