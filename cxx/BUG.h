#ifndef KERNEL_CXX_BUG_H_INCLUDED
#define KERNEL_CXX_BUG_H_INCLUDED

#include "Message.h"
#include <generic/Utils.h>

#define BUG(message) \
	do { \
		::kernel::Message::fatal << "BUG: " << ::kernel::Utils::basename(__FILE__) <<  ":" \
				 << __LINE__ << " " << message << "\n"; \
		for (;;); \
	} while (0)

#endif /* KERNEL_CXX_BUG_H_INCLUDED */
