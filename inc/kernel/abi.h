#ifndef KERNEL_ABI_H_INCLUDED
#define KERNEL_ABI_H_INCLUDED

#include <DEFINE.h>

BEGIN_DEFINE(KernelApplicationBinaryInterfaceConstant)

/* !!!!!!!!!!!!!!!
 * !!! Warning !!!
 * !!!!!!!!!!!!!!!
 * If you want to change these variables, make sure you have also changed the corresponding
 * linker scripts.
 */
DEFINE_LONG_LONG(KERNEL_VIRTUAL_BASE, 0xFFFF800000000000)
DEFINE(KERNEL_RESERVED_MEMORY, 0x100000)
DEFINE(KERNEL_TEMP_AREA, 0xA000)
DEFINE(KERNEL_STACK_SIZE, 0x6000)
DEFINE(KERNEL_STACK_TOP, KERNEL_VIRTUAL_BASE + KERNEL_RESERVED_MEMORY + KERNEL_TEMP_AREA)
DEFINE(KERNEL_STACK_BOTTOM, KERNEL_STACK_TOP + KERNEL_STACK_SIZE)
DEFINE(KERNEL_PHYSICAL_BASE, KERNEL_RESERVED_MEMORY + KERNEL_TEMP_AREA + KERNEL_STACK_SIZE)
DEFINE(KERNEL_TEMP_AREA_BEGIN, KERNEL_STACK_TOP - KERNEL_TEMP_AREA)
DEFINE(KERNEL_TEMP_AREA_END, KERNEL_STACK_TOP)

END_DEFINE()

#endif /* KERNEL_ABI_H_INCLUDED */
