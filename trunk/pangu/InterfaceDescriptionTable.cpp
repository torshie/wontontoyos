#include "InterfaceDescriptionTable.h"
#include "Message.h"

using namespace kernel;

namespace pangu {

void InterfaceDescriptionTable::show() {
	Message::brief << "Signature: " << signature[0] << signature[1] << signature[2] << signature[3] << "\n"
			<< "Length: " << length << "\n"
			<< "OemId: " << oemId << "\n"
			<< "OemTableId: " << oemTableId << "\n"
			<< "OemRevision: " << oemRevision << "\n"
			<< "CreatorId: " << creatorId << "\n"
			<< "CreatorRevision: " << creatorRevision << "\n";
}

} // namespace pangu
