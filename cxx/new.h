#ifndef KERNEL_CXX_NEW_H_INCLUDED
#define KERNEL_CXX_NEW_H_INCLUDED

#include <generic/type.h>

void* operator new(kernel::Size, void* p);
void* operator new[](kernel::Size, void* p);

inline void* operator new(kernel::Size, void* p) {
	return p;
}

#endif // KERNEL_CXX_NEW_H_INCLUDED
