#ifndef KERNEL_CXX_ABORT_H_INCLUDED
#define KERNEL_CXX_ABORT_H_INCLUDED

namespace std {

void abort() __attribute__((__noreturn__));

}

#endif // KERNEL_CXX_ABORT_H_INCLUDED
