#ifndef KERNEL_EXE_ELF64_H_INCLUDED
#define KERNEL_EXE_ELF64_H_INCLUDED

#include <generic/type.h>

namespace kernel {

struct Elf64Header {
	struct {
		U8 mag0;
		U8 mag1;
		U8 mag2;
		U8 mag3;
		U8 fileClass;
		U8 dataEncoding;
		U8 fileVersion;
		U8 abiId;
		U8 abiVersion;
		U8 _pad[7];
	};
	U16 type;
	U16 machine;
	U32 version;
	U64 entryPoint;
	U64 programHeaderOffset;
	U64 sectionHeaderOffset;
	U32 flags;
	U16 headerSize;
	U16 programHeaderSize;
	U16 programHeaderCount;
	U16 sectionHeaderSize;
	U16 sectionHeaderCount;
	U16 sectionNameStringTableIndex;

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
	U32 name;
	U32 type;
	U64 flags;
	U64 address;
	U64 offset;
	U64 size;
	U32 link;
	U32 misc;
	U64 align;
	U64 entrySize;

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
	U32 name;
	U8 flags;
	U8 reserved;
	U16 sectionTableIndex;
	U64 value;
	U64 size;

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
	U32 type;
	U32 flags;
	U64 offset;
	U64 address;
	U64 reserved;
	U64 fileSize;
	U64 memorySize;
	U64 align;

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

} /* namespace kernel */

#endif /* KERNEL_EXE_ELF64_H_INCLUDED */

