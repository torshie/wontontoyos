#ifndef __WONTON_CXX_INIT_CXX_SUPPORT_H_INCLUDED__
#define __WONTON_CXX_INIT_CXX_SUPPORT_H_INCLUDED__

namespace cxx {
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

}

#endif
