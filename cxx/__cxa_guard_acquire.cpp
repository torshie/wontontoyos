#include <base/type.h>

extern "C" int __cxa_guard_acquire(base::U64* guard) {
	return !(*((char*)guard));
}
