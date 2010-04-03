#include "abort.h"

extern "C" void __cxa_pure_virtual() {
	std::abort();
}
