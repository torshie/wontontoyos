#ifndef KERNEL_CXX_INIT_CXX_SUPPORT_H_INCLUDED
#define KERNEL_CXX_INIT_CXX_SUPPORT_H_INCLUDED

namespace kernel {
/**
 * Initialize C++ support library libcxx
 *
 * This function will do enough initialization to the early execution
 * environment, so that advanced C++ features like global objects can
 * work correctly.
 *
 * @return On success return 0, on failure return non-zero
 */
int initCxxSupport();

} /* namespace kernel */

#endif /* KERNEL_CXX_INIT_CXX_SUPPORT_H_INCLUDED */
