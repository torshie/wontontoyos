#include "abort.h"

extern "C" void __cxa_bad_typeid() {
	std::abort();
}
