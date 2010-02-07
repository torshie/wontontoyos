#ifndef KERNEL_ARCH_PAGE_MAP_H_INCLUDED
#define KERNEL_ARCH_PAGE_MAP_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class PageMap {
public:
	static void* mapTempPage(Address physicalAddress);
	static Address unmapTempPage(void*);

	static void reload();
};

} /* namespace kernel */

#endif /* KERNEL_ARCH_PAGE_MAP_H_INCLUDED */
