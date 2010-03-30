#ifndef KERNEL_EXE_SIMPLE_LOADER_H_INCLUDED
#define KERNEL_EXE_SIMPLE_LOADER_H_INCLUDED

#include <exe/FileHeader.h>

namespace kernel {
/**
 * A simple elf64 executable loader.
 *
 * This simple loader can only load *static* linked elf64 executable. It lacks many necessary
 * checks, so it can only be used to load *trusted* elf64 binaries.
 */
class SimpleLoader {
public:
	int parse(const void* image, Size size);

	Address getBaseAddress() {
		return base;
	}

	Size getMemoryImageSize() {
		return memoryImageSize;
	}

	Address load(Size size);

private:
	FileHeader* header;
	Address base;
	Size memoryImageSize;
};

} // namespace kernel

#endif // KERNEL_EXE_SIMPLE_LOADER_H_INCLUDED
