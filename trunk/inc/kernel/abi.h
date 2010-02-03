#ifndef KERNEL_ABI_H_INCLUDED
#define KERNEL_ABI_H_INCLUDED

#include <DEFINE.h>

BEGIN_DEFINE(kernel)

/**
 * !!!!!!!!!!!!!!!
 * !!! Warning !!!
 * !!!!!!!!!!!!!!!
 * If you want to change variables in this file, make sure you have also
 * changed the corresponding linker scripts.
 */
DEFINE(KERNEL_VIRTUAL_BASE, 0xFFFFFF0000000000)
DEFINE(KERNEL_LOAD_ADDRESS, 0x105000)

END_DEFINE()

#endif /* KERNEL_ABI_H_INCLUDED */
