#ifndef KERNEL_ARCH_PAGE_POINTER_H_INCLUDED
#define KERNEL_ARCH_PAGE_POINTER_H_INCLUDED

#include <generic/type.h>
#include <generic/STATIC_ASSERT.h>
#include "arch/X64Constant.h"
#include <cxx/BUG.h>
#include <kernel/abi.h>

namespace kernel {

template<int LEVEL> class PageTable;

template<int LEVEL> class PagePointer {
public:
	PagePointer() : __initializer(0) {}

	enum __ {
		PRESENT = 1 << 0,
		WRITABLE = 1 << 1,
		USER_SPACE = 1 << 2,
		WRITE_THROUGH = 1 << 3,
		CACHE_DISABLE = 1 << 4,
		ACCESSED = 1 << 5,
		DIRTY = 1 << 6,
		GLOBAL = 1 << 8,
		NO_EXECUTE = (U64)1 << 63,
		POINTERS_PER_PAGE = PAGE_SIZE / sizeof(U64),

		MEMORY_POINTED = (LEVEL == 1) ? (U64)PAGE_SIZE
				: (U64)POINTERS_PER_PAGE * PagePointer<LEVEL - 1>::MEMORY_POINTED
	};

	union {
		U64 __initializer;

		struct {
			U8 present:1;
			U8 writable:1;
			U8 userSpace:1;
			U8 writeThrough:1;
			U8 cacheDisable:1;
			U8 accessed:1;
			U8 dirty:1;
			U8 __pat:1;
			U8 global:1;
			U8 __reserved_1:3;
			U64 page:40;
			U16 __reserved_2:11;
			U8 noExecute:1;
		} __attribute__((packed));

		U64 address;
	};

	static PagePointer* getPointerTo(Address address) {
		if (address < KERNEL_VIRTUAL_BASE) {
			return getPointerToUserAddress(address);
		} else {
			return getPointerToKernelAddress(address);
		}
	}

private:
	static PagePointer* getPointerToKernelAddress(Address virtualAddress) {
		Address alignedAddress = virtualAddress / MEMORY_POINTED * MEMORY_POINTED;
		U64 pointerCount = (-alignedAddress) / MEMORY_POINTED;
		U64 spaceUsed = pointerCount * sizeof(PagePointer);
		return (PagePointer*)(-spaceUsed);
	}

	static PagePointer* getPointerToUserAddress(Address virtualAddress) {
		Address pointerOffset = virtualAddress / MEMORY_POINTED;
		return (PagePointer*)(pointerOffset * sizeof(PagePointer)
				+ PageTable<LEVEL>::LOWEST_TABLE_ADDRESS);
	}
} __attribute__((packed));

template<> class PagePointer<0> {
public:
	enum {
		MEMORY_POINTED = 1
	};
};

STATIC_ASSERT_EQUAL(sizeof(PagePointer<1>), 8)
STATIC_ASSERT_EQUAL(sizeof(PagePointer<2>), 8)
STATIC_ASSERT_EQUAL(sizeof(PagePointer<3>), 8)
STATIC_ASSERT_EQUAL(sizeof(PagePointer<4>), 8)
STATIC_ASSERT_EQUAL(PagePointer<1>::MEMORY_POINTED, PAGE_SIZE)
STATIC_ASSERT_EQUAL(PagePointer<2>::MEMORY_POINTED, PAGE_SIZE * 512)
STATIC_ASSERT_EQUAL(PagePointer<3>::MEMORY_POINTED, PAGE_SIZE * 512 * 512)
STATIC_ASSERT_EQUAL(PagePointer<4>::MEMORY_POINTED, PAGE_SIZE * 512LL * 512 * 512)

} // namespace kernel

#endif // KERNEL_ARCH_PAGE_POINTER_H_INCLUDED
