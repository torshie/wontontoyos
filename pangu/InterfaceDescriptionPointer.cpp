#include "InterfaceDescriptionPointer.h"
#include <generic/Utils.h>

using namespace kernel;

namespace pangu {

const InterfaceDescriptionPointer* InterfaceDescriptionPointer::find() {
	enum {
		MIN_POSSIBLE_ADDRESS = 0x0009FC00,
		MAX_POSSIBLE_ADDRESS = 0x000FFFFF - sizeof(InterfaceDescriptionPointer)
	};
	const char* const SIGNATURE = "RSD PTR ";

	for (const char* needle = (const char*)MIN_POSSIBLE_ADDRESS;
			needle < (const char*)MAX_POSSIBLE_ADDRESS; ++needle) {
		if (Utils::strcmp(SIGNATURE, needle, Utils::strlen(SIGNATURE)) == 0) {
			return (InterfaceDescriptionPointer*)needle;
		}
	}
	return 0;
}

} // namespace pangu
