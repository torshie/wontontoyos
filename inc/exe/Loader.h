#ifndef KERNEL_EXE_LOADER_H_INCLUDED
#define KERNEL_EXE_LOADER_H_INCLUDED

#include <generic/type.h>

namespace kernel {

/**
 * Executable loader interface
 */
class Loader {
public:
	virtual ~Loader() {}

	/**
	 * Parse an executable image.
	 * The memory pointed by "image" shouldn't be changed until the
	 * method load() is called, otherwise the behaviors of methods
	 * getBaseAddress(), getMemoryImageSize() and load() are undefined
	 *
	 * @param image The address of the executable image
	 * @param size The size of the executable image
	 * @return On success returns 0, otherwise return error code, the
	 * error code is implementation dependent.
	 */
	virtual int parse(const void* image, Size size) = 0;

	/**
	 * Get the base address of the memory image of the executable
	 * This method should be called after method parse() is called,
	 * otherwise the behavior of this method is undefined
	 *
	 * @return The base address of the executable
	 *
	 * @see parse()
	 */
	virtual Address getBaseAddress() = 0;

	/**
	 * Get the size of the memory image of the executable
	 * This method should be called after method parse() is called,
	 * otherwise the behavior of this method is undefined
	 *
	 * @return The size of the memory needed
	 *
	 * @see parse()
	 */
	virtual Size getMemoryImageSize() = 0;

	/**
	 * Load the executable into memory.
	 * This method will create a correct memory image of the given
	 * executable. This method should be called after method parse() is
	 * called, otherwise the behavior is undefined.
	 *
	 * @param base The base address of the memory that the memory image
	 * will be written into
	 * @param size The size of the available space that the parameter
	 * base points to
	 * @return The entry point of the executable
	 *
	 * @see parse()
	 */
	virtual Address load(void* base, Size size) = 0;
};

} /* namespace kernel */

#endif /* KERNEL_EXE_LOADER_H_INCLUDED */
