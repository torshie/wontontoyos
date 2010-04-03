#ifndef PANGU_INTERFACE_DESCRIPTION_POINTER_H_INCLUDED
#define PANGU_INTERFACE_DESCRIPTION_POINTER_H_INCLUDED

#include <generic/type.h>

namespace pangu {

class InterfaceDescriptionTable;
class InterfaceDescriptionPointer {
	~InterfaceDescriptionPointer();
public:
	static const InterfaceDescriptionPointer* find();

	const InterfaceDescriptionTable* getRootTable() const {
		return (InterfaceDescriptionTable*)address;
	}

	kernel::U8 signature[8];
	kernel::U8 checksum;
	kernel::U8 oemId[6];
	kernel::U8 revision;
	kernel::U32 address;
} __attribute__((packed));

} // namespace pangu

#endif // PANGU_INTERFACE_DESCRIPTION_POINTER_H_INCLUDED
