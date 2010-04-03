#ifndef KERNEL_SUPCXX_STDDEF_H_INCLUDED
#define KERNEL_SUPCXX_STDDEF_H_INCLUDED

#include <generic/type.h>

namespace std {

typedef ::kernel::Size size_t;
typedef long ptrdiff_t;

}

#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)

#endif // KERNEL_SUPCXX_STDDEF_H_INCLUDED
