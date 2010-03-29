#ifndef PANGU_INTERFACE_DESCRIPTION_TABLE_H_INCLUDED
#define PANGU_INTERFACE_DESCRIPTION_TABLE_H_INCLUDED

#include <generic/type.h>

namespace pangu {

class InterfaceDescriptionTable {
	~InterfaceDescriptionTable();

public:
	void show();

	char signature[4];
	kernel::U32 length;
	kernel::U8 revision;
	kernel::U8 checksum;
	char oemId[6];
	char oemTableId[8];
	kernel::U32 oemRevision;
	kernel::U32 creatorId;
	kernel::U32 creatorRevision;
} __attribute__((packed));

} // namespace pangu

#endif // PANGU_INTERFACE_DESCRIPTION_TABLE_H_INCLUDED
