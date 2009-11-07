#ifndef __WONTON_EXE_SIMPLE_LOADER_H_INCLUDED__
#define __WONTON_EXE_SIMPLE_LOADER_H_INCLUDED__

#include <exe/Loader.h>
#include <exe/elf64.h>

namespace exe {
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
	int parse(const void* image, kernel::Size size);

	/**
	 * Get the base address of the memory image
	 *
	 * @see Loader::getBaseAddress()
	 */
	kernel::Address getBaseAddress();

	/**
	 * Get the size of the of the memory image
	 *
	 * @see Loader::getMemoryImageSize()
	 */
	kernel::Size getMemoryImageSize();

	/**
	 * Load the elf64 into memory
	 *
	 * @see Loader::load()
	 */
	kernel::Address load(void* base, kernel::Size size);

private:
	/**
	 * ELF64 header of the elf64 executable
	 */
	Elf64Header* header;

	/**
	 * Base address of the memory image
	 */
	kernel::Address base;

	/**
	 * Size of the memory image
	 */
	kernel::Size memoryImageSize;
};

inline kernel::Address SimpleLoader::getBaseAddress() {
	return base;
}

inline kernel::Size SimpleLoader::getMemoryImageSize() {
	return memoryImageSize;
}

}

#endif
