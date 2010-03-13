#include "mm/GenericAllocator.h"

using namespace kernel;

void operator delete(void* pointer) {
	getSingleInstance<GenericAllocator>().release(pointer);
}
