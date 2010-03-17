#include <exe/SimpleLoader.h>
#include <kernel/abi.h>
#include <generic/type.h>

using namespace kernel;

extern "C" Address loadKernelImage(FileHeader* fileHeader, Size size) {
	SimpleLoader loader;
	loader.parse(fileHeader, size);
	Size memoryImageSize = loader.getMemoryImageSize();
	return loader.load((void*)(KERNEL_PHYSICAL_BASE), memoryImageSize);
}
