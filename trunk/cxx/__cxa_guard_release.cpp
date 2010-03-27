#include <generic/type.h>

// XXX Check correctness of this function
extern "C" void __cxa_guard_release(kernel::U64* guard) {
	*((char*)(guard)) = 1;
}
