#ifndef KERNEL_ABI_H_INCLUDED
#define KERNEL_ABI_H_INCLUDED

#include <DEFINE.h>

BEGIN_DEFINE(KernelApplicationBinaryInterfaceConstant)

/**
 * If you want to change these variables, make sure the corresponding linker scripts are
 * consistent and clean the build tree before testing.
 */
DEFINE_LONG_LONG(KERNEL_VIRTUAL_BASE, 0xFFFF800000000000)
DEFINE(LOW_MEMORY_SIZE, 0x100000)
DEFINE(MEMORY_HOLE_SIZE, 0x4000)
DEFINE(TEMP_MAP_SIZE, 0x7000)

DEFINE(KERNEL_HOLE_BASE, KERNEL_VIRTUAL_BASE + LOW_MEMORY_SIZE)
DEFINE(KERNEL_STACK_TOP, KERNEL_HOLE_BASE + MEMORY_HOLE_SIZE)
DEFINE(KERNEL_STACK_SIZE, TEMP_MAP_SIZE + 0x1000)
DEFINE(KERNEL_STACK_BOTTOM, KERNEL_STACK_TOP + KERNEL_STACK_SIZE)

/* The address pointed by the second level four user space pointer */
DEFINE_LONG_LONG(USER_VIRTUAL_BASE, 0x8000000000)

/* The address pointed by the last level four user space pointer */
DEFINE_LONG_LONG(USER_STACK_BOTTOM, 0x800000000000)

DEFINE(SYSCALL_MIN, 0)
DEFINE(SYSCALL_EXIT_PROCESS, SYSCALL_MIN + 0)
DEFINE(SYSCALL_RETURN_VALUE, SYSCALL_MIN + 1)
DEFINE(SYSCALL_PRINT, SYSCALL_MIN + 2)
DEFINE(SYSCALL_SLEEP, SYSCALL_MIN + 3)
DEFINE(SYSCALL_COUNT, 4) /* Don't forget to update this constant after add a new system call */
DEFINE(SYSCALL_MAX, SYSCALL_COUNT - 1)

DEFINE(VIRTUAL_BASE_APIC, KERNEL_HOLE_BASE)
DEFINE(MEMORY_SIZE_APIC, 0x1000)
DEFINE(VIRTUAL_BASE_IOAPIC, VIRTUAL_BASE_APIC + MEMORY_SIZE_APIC)
DEFINE(MEMORY_SIZE_IOAPIC, 0x1000)
DEFINE(VIRTUAL_BASE_HPET, VIRTUAL_BASE_IOAPIC + MEMORY_SIZE_IOAPIC)
DEFINE(MEMORY_SIZE_HPET, 0x1000)

END_DEFINE()

#endif /* KERNEL_ABI_H_INCLUDED */
