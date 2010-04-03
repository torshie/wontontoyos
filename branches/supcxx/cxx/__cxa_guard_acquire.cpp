#include <generic/type.h>

// XXX Check correctness of this function
extern "C" int __cxa_guard_acquire(kernel::U64* guard) {
	return !(*((char*)guard));
}
