#include "mm/GenericAllocator.h"
#include <generic/type.h>

using namespace kernel;

void* operator new (Size size) {
	return getSingleInstance<GenericAllocator>().allocate(size);
}

void* operator new(Size, void* p) {
	return p;
}
