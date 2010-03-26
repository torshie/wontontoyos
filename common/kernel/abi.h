#ifndef KERNEL_ABI_H_INCLUDED
#define KERNEL_ABI_H_INCLUDED

#include <DEFINE.h>

BEGIN_DEFINE(KernelApplicationBinaryInterfaceConstant)

/* !!!!!!!!!!!!!!!
 * !!! Warning !!!
 * !!!!!!!!!!!!!!!
 * If you want to change these variables, make sure the corresponding linker scripts are consistent
 */
DEFINE_LONG_LONG(KERNEL_VIRTUAL_BASE, 0xFFFF800000000000)
DEFINE(KERNEL_RESERVED_MEMORY, 0x100000)
DEFINE(APIC_MEMORY_SIZE, 0x1000)
DEFINE(KERNEL_STACK_SIZE, 0x6000)
DEFINE(KERNEL_STACK_TOP, KERNEL_VIRTUAL_BASE + KERNEL_RESERVED_MEMORY + APIC_MEMORY_SIZE)
DEFINE(KERNEL_STACK_BOTTOM, KERNEL_STACK_TOP + KERNEL_STACK_SIZE)
DEFINE(KERNEL_PHYSICAL_BASE, KERNEL_RESERVED_MEMORY + APIC_MEMORY_SIZE + KERNEL_STACK_SIZE)
DEFINE(KERNEL_TEMP_AREA_BEGIN, KERNEL_STACK_TOP - APIC_MEMORY_SIZE)
DEFINE(KERNEL_TEMP_AREA_END, KERNEL_STACK_TOP)

DEFINE_LONG_LONG(USER_VIRTUAL_BASE, 0x8000000000)
DEFINE_LONG_LONG(USER_STACK_BOTTOM, 0x800000000000)

DEFINE(SYSCALL_MIN, 0)
DEFINE(SYSCALL_EXIT_PROCESS, SYSCALL_MIN + 0)
DEFINE(SYSCALL_RETURN_VALUE, SYSCALL_MIN + 1)
DEFINE(SYSCALL_PRINT, SYSCALL_MIN + 2)
DEFINE(SYSCALL_SUM, SYSCALL_MIN + 3)
DEFINE(SYSCALL_COUNT, 4) /* Don't forget to update this constant after add a new system call */
DEFINE(SYSCALL_MAX, SYSCALL_COUNT - 1)

END_DEFINE()

#endif /* KERNEL_ABI_H_INCLUDED */