#ifndef KERNEL_CXX_BUG_H_INCLUDED
#define KERNEL_CXX_BUG_H_INCLUDED

#include "Printer.h"
#include <generic/Utils.h>

#define BUG(message) \
	do { \
		::kernel::Printer& console = getSingleInstance< ::kernel::Printer>(); \
		console << "BUG: " << ::kernel::Utils::basename(__FILE__) <<  ":" << __LINE__ \
				<< " " << message << "\n"; \
		for (;;); \
	} while (0)

#endif /* KERNEL_CXX_BUG_H_INCLUDED */
