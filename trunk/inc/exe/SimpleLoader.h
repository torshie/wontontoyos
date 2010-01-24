#ifndef KERNEL_EXE_SIMPLE_LOADER_H_INCLUDED
#define KERNEL_EXE_SIMPLE_LOADER_H_INCLUDED

#include <exe/Loader.h>
#include <exe/elf64.h>

namespace kernel {
/**
 * A simple elf64 executable loader.
 * This simple loader can only load *static* linked elf64 executable. It
 * lacks many necessary checks, so it can only be used to load *trusted*
 * elf64 binaries.
 */
class SimpleLoader : public Loader {
public:
	/**
	 * Parse elf64 executable
	 *
	 * @see Loader::parse()
	 */
	int parse(const void* image, Size size);

	/**
	 * Get the base address of the memory image
	 *
	 * @see Loader::getBaseAddress()
	 */
	Address getBaseAddress();

	/**
	 * Get the size of the of the memory image
	 *
	 * @see Loader::getMemoryImageSize()
	 */
	Size getMemoryImageSize();

	/**
	 * Load the elf64 into memory
	 *
	 * @see Loader::load()
	 */
	Address load(void* base, Size size);

private:
	/**
	 * ELF64 header of the elf64 executable
	 */
	Elf64Header* header;

	/**
	 * Base address of the memory image
	 */
	Address base;

	/**
	 * Size of the memory image
	 */
	Size memoryImageSize;
};

inline Address SimpleLoader::getBaseAddress() {
	return base;
}

inline Size SimpleLoader::getMemoryImageSize() {
	return memoryImageSize;
}

} /* namespace kernel */

#endif /* KERNEL_EXE_SIMPLE_LOADER_H_INCLUDED */
