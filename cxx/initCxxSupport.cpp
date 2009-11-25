#include <cxx/initCxxSupport.h>

namespace cxx {

typedef void (*Constructor)(void);

/**
 * These two variables are defined in ld script.
 */
extern "C" Constructor __ld_start_ctors;
extern "C" Constructor __ld_end_ctors;
static void constructGlobalObjects(void) {
	for (Constructor* ctor = &__ld_start_ctors; ctor < &__ld_end_ctors;
			++ctor) {
		(*ctor)();
	}
}

int initCxxSupport() {
	constructGlobalObjects();
	return 0;
}

}
