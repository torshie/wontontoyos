#include "abort.h"

extern "C" int __cxa_atexit(void (*)(void*), void*, void*) {
	std::abort();
}
