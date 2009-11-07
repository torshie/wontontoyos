#include <exe/SimpleLoader.h>
#include <util/Memory.h>

using namespace kernel;
using namespace util;

namespace exe {

int SimpleLoader::parse(const void* image, Size) {
	header = (Elf64Header*)image;

	SectionHeader* section = (SectionHeader*)((char*)header +
			header->sectionHeaderOffset);

	base = ~((Address)0); /* Set base to an invalid address */
	Address upper = 0; /* Upper bound of the memory image */

	for (Size i = 0; i < header->sectionHeaderCount; ++i) {
		if (section[i].flags & SectionHeader::FLAG_ALLOCATE) {
			if (section[i].address < base) {
				base = section[i].address;
			}
			if (section[i].size + section[i].address > upper) {
				upper = section[i].size + section[i].address;
			}
		}
	}

	memoryImageSize = upper - base;

	return 0;
}

Address SimpleLoader::load(void* base, Size) {
	SectionHeader* section = (SectionHeader*) ((char*)header
			+ header->sectionHeaderOffset);
	Address b = getBaseAddress();
	for (Size i = 0; i < header->sectionHeaderCount; ++i) {
		if (section[i].flags & SectionHeader::FLAG_ALLOCATE) {
			Address offset = section[i].address - b;
			if (section[i].type == SectionHeader::TYPE_PROGRAM_BITS) {
				Memory::memcpy((char*) base + offset, (char*)header
						+ section[i].offset, section[i].size);
			} else {
				Memory::zeroize((char*)base + offset, section[i].size);
			}
		}
	}

	return header->entryPoint;
}

}
