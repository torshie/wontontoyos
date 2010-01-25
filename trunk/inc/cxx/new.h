#ifndef KERNEL_CXX_NEW_H_INCLUDED
#define KERNEL_CXX_NEW_H_INCLUDED

inline void* operator new(unsigned long, void* p) {
	return p;
}

#endif /* KERNEL_CXX_NEW_H_INCLUDED */
