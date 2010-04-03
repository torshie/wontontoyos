#ifndef KERNEL_OFFSET_OF_H_INCLUDED
#define KERNEL_OFFSET_OF_H_INCLUDED

#include <generic/type.h>

#define OFFSET_OF(Type, member) ((::kernel::Offset)(&(reinterpret_cast<Type*>(1)->member)) - 1)

#endif // KERNEL_OFFSET_OF_H_INCLUDED
