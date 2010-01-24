#include <exe/SimpleLoader.h>
#include <kernel/abi.h>

using namespace kernel;

extern "C" Address loadKernelImage(Elf64Header* fileHeader, Size size) {
	SimpleLoader loader;
	loader.parse(fileHeader, size);
	Size memoryImageSize = loader.getMemoryImageSize();
	return loader.load((void*)(KERNEL_LOAD_ADDRESS), memoryImageSize);
}
