#include <exe/SimpleLoader.h>
#include <generic/type.h>

using namespace kernel;

extern "C" Address loadFileImage(FileHeader* fileHeader, Size size) {
	SimpleLoader loader;
	loader.parse(fileHeader, size);
	Size memoryImageSize = loader.getMemoryImageSize();
	return loader.load(memoryImageSize);
}
