#ifndef __WONTON_EXE_ELF64_H__
#define __WONTON_EXE_ELF64_H__

#include <base/type.h>

namespace exe {

struct Elf64Header {
	struct {
		base::U8 mag0;
		base::U8 mag1;
		base::U8 mag2;
		base::U8 mag3;
		base::U8 fileClass;
		base::U8 dataEncoding;
		base::U8 fileVersion;
		base::U8 abiId;
		base::U8 abiVersion;
		base::U8 _pad[7];
	};
	base::U16 type;
	base::U16 machine;
	base::U32 version;
	base::U64 entryPoint;
	base::U64 programHeaderOffset;
	base::U64 sectionHeaderOffset;
	base::U32 flags;
	base::U16 headerSize;
	base::U16 programHeaderSize;
	base::U16 programHeaderCount;
	base::U16 sectionHeaderSize;
	base::U16 sectionHeaderCount;
	base::U16 sectionNameStringTableIndex;

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
	base::U32 name;
	base::U32 type;
	base::U64 flags;
	base::U64 address;
	base::U64 offset;
	base::U64 size;
	base::U32 link;
	base::U32 misc;
	base::U64 align;
	base::U64 entrySize;

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
	base::U32 name;
	base::U8 flags;
	base::U8 reserved;
	base::U16 sectionTableIndex;
	base::U64 value;
	base::U64 size;

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
	base::U32 type;
	base::U32 flags;
	base::U64 offset;
	base::U64 address;
	base::U64 reserved;
	base::U64 fileSize;
	base::U64 memorySize;
	base::U64 align;

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

