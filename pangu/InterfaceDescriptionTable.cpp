#include "InterfaceDescriptionTable.h"
#include "Message.h"
#include <generic/Utils.h>

using namespace kernel;

namespace pangu {

const InterfaceDescriptionTable* InterfaceDescriptionTable::find(const char* sig) const {
	for (U32* start = (U32*)data; (char*)start < (char*)this + length; ++start) {
		if (*start != 0) {
			const InterfaceDescriptionTable* table = (const InterfaceDescriptionTable*)*start;
			if (Utils::strcmp(table->signature, sig, sizeof(table->signature)) == 0) {
				return table;
			}
		}
	}
	return 0;
}

} // namespace pangu
