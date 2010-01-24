#include <generic/type.h>

extern "C" int __cxa_guard_acquire(kernel::U64* guard) {
	return !(*((char*)guard));
}
