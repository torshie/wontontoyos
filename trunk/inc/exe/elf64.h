#ifndef __WONTON_EXE_ELF64_H__
#define __WONTON_EXE_ELF64_H__

#include <kernel/type.h>

namespace exe {

struct Elf64Header {
	struct {
		kernel::U8 mag0;
		kernel::U8 mag1;
		kernel::U8 mag2;
		kernel::U8 mag3;
		kernel::U8 fileClass;
		kernel::U8 dataEncoding;
		kernel::U8 fileVersion;
		kernel::U8 abiId;
		kernel::U8 abiVersion;
		kernel::U8 _pad[7];
	};
	kernel::U16 type;
	kernel::U16 machine;
	kernel::U32 version;
	kernel::U64 entryPoint;
	kernel::U64 programHeaderOffset;
	kernel::U64 sectionHeaderOffset;
	kernel::U32 flags;
	kernel::U16 headerSize;
	kernel::U16 programHeaderSize;
	kernel::U16 programHeaderCount;
	kernel::U16 sectionHeaderSize;
	kernel::U16 sectionHeaderCount;
	kernel::U16 sectionNameStringTableIndex;

	enum {
		FILE_CLASS_32 = 1,
		FILE_CLASS_64 = 2,
		DATA_ENCODING_LSB = 1,
		DATA_ENCODING_MSB = 2,
		ABI_ID_SYSV = 0,
		ABI_ID_HPUX = 1,
		ABI_ID_STANDALONE = 255,

		TYPE_NONE = 0,
		TYPE_RELOCATABLE = 1,
		TYPE_EXECUTABLE = 2,
		TYPE_DYNAMIC = 3,
		TYPE_CORE = 4,
	};
};

struct SectionHeader {
	kernel::U32 name;
	kernel::U32 type;
	kernel::U64 flags;
	kernel::U64 address;
	kernel::U64 offset;
	kernel::U64 size;
	kernel::U32 link;
	kernel::U32 misc;
	kernel::U64 align;
	kernel::U64 entrySize;

	enum {
		TYPE_NULL = 0,
		TYPE_PROGRAM_BITS = 1,
		TYPE_SYMBOL_TABLE = 2,
		TYPE_STRING_TABLE = 3,
		TYPE_RELA = 4,
		TYPE_HASH_TABLE = 5,
		TYPE_DYNAMIC_LINKING_TABLE = 6,
		TYPE_NOTE_INFORMATION = 7,
		TYPE_UNINITIALIZED_BITS = 8,
		TYPE_REL = 9,
		TYPE_RESERVED = 10,
		TYPE_DYNAMIC_LOADER_SYMBOL_TABLE = 11,

		FLAG_WRITABLE = 0x1,
		FLAG_ALLOCATE = 0x2,
		FLAG_EXECUTABLE = 0x4,
	};
};

struct Symbol {
	kernel::U32 name;
	kernel::U8 flags;
	kernel::U8 reserved;
	kernel::U16 sectionTableIndex;
	kernel::U64 value;
	kernel::U64 size;

	enum {
		BINDING_LOCAL = 0,
		BINDING_GLOBAL = 1,
		BINDING_WEAK = 2,

		TYPE_NONE = 0,
		TYPE_DATA_OBJECT = 1,
		TYPE_FUNCTION = 2,
		TYPE_SECTION = 3,
		TYPE_FILE = 4
	};
};

struct ProgramHeader {
	kernel::U32 type;
	kernel::U32 flags;
	kernel::U64 offset;
	kernel::U64 address;
	kernel::U64 reserved;
	kernel::U64 fileSize;
	kernel::U64 memorySize;
	kernel::U64 align;

	enum {
		TYPE_NULL = 0,
		TYPE_LOADABLE = 1,
		TYPE_DYNAMIC_LINKING = 2,
		TYPE_INTERPRETER_NAME = 3,
		TYPE_NOTE = 4,
		TYPE_RESERVED = 5,
		TYPE_PROGRAM_HEADER_TABLE = 6,

		FLAG_EXECUTABLE = 1,
		FLAG_WRITABLE = 2,
		FLAG_READABLE = 3
	};
};

} /* namespace exe */

#endif

