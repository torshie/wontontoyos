#include "initCxxSupport.h"

namespace kernel {

typedef void (*Initializer)(void);

/**
 * These two variables are defined in ld script.
 */
extern "C" Initializer __ld_start_ctors;
extern "C" Initializer __ld_end_ctors;
static void initializeGlobalObjects(void) {
	for (Initializer* ctor = &__ld_start_ctors; ctor < &__ld_end_ctors; ++ctor) {
		(*ctor)();
	}
}

int initCxxSupport() {
	initializeGlobalObjects();
	return 0;
}

}
