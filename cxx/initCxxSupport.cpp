#include "initCxxSupport.h"

namespace kernel {

typedef void (*Initializer)(void);

// These two variables are defined in ld script.
extern "C" Initializer __ld_start_ctors;
extern "C" Initializer __ld_end_ctors;
static void initializeGlobalObjects(void) {
	for (Initializer* initializer = &__ld_start_ctors; initializer < &__ld_end_ctors;
			++initializer) {
		(*initializer)();
	}
}

// XXX Initialize other support components, for example, exception support.
int initCxxSupport() {
	initializeGlobalObjects();
	return 0;
}

}
