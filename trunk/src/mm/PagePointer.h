#ifndef KERNEL_ARCH_PAGE_POINTER_H_INCLUDED
#define KERNEL_ARCH_PAGE_POINTER_H_INCLUDED

#include <generic/type.h>
#include <generic/STATIC_ASSERT.h>
#include "arch/X64Constant.h"
#include <cxx/BUG.h>
#include <kernel/abi.h>

namespace kernel {

template<int LEVEL>
class PagePointer {
	PagePointer(const PagePointer&);
	const PagePointer& operator = (const PagePointer&);
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
		NUMBER_OF_POINTERS_PER_PAGE = PAGE_SIZE / sizeof(U64),

		SIZE_OF_POINTED_MEMORY =
				(LEVEL == 1) ? (U64)PAGE_SIZE
						: (U64)NUMBER_OF_POINTERS_PER_PAGE
								* PagePointer<LEVEL - 1>::SIZE_OF_POINTED_MEMORY
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

		U64 physicalAddress;
	};

	static PagePointer* getPointerToKernelAddress(void* pointer) {
		return getPointerToKernelAddress((Address)pointer);
	}

	static PagePointer* getPointerToKernelAddress(Address virtualAddress) {
		if (virtualAddress < KERNEL_VIRTUAL_BASE) {
			BUG("Invalid kernel address " << virtualAddress);
		}

		Address alignedAddress = virtualAddress / SIZE_OF_POINTED_MEMORY
				* SIZE_OF_POINTED_MEMORY;

		U64 pointerCount = (-alignedAddress) / SIZE_OF_POINTED_MEMORY;
		U64 spaceUsed = pointerCount * sizeof(PagePointer);
		return (PagePointer*)(-spaceUsed);
	}
} __attribute__((packed));

// XXX Find out why we need this to terminate template recursive instantiation, and remove
// this template specialization
template<>
class PagePointer<0> {
public:
	enum {
		SIZE_OF_POINTED_MEMORY = 1
	};
};

STATIC_ASSERT_EQUAL(sizeof(PagePointer<1>), 8)
STATIC_ASSERT_EQUAL(sizeof(PagePointer<2>), 8)
STATIC_ASSERT_EQUAL(sizeof(PagePointer<3>), 8)
STATIC_ASSERT_EQUAL(sizeof(PagePointer<4>), 8)
STATIC_ASSERT_EQUAL(PagePointer<1>::SIZE_OF_POINTED_MEMORY, PAGE_SIZE)
STATIC_ASSERT_EQUAL(PagePointer<2>::SIZE_OF_POINTED_MEMORY, PAGE_SIZE * 512)
STATIC_ASSERT_EQUAL(PagePointer<3>::SIZE_OF_POINTED_MEMORY, PAGE_SIZE * 512 * 512)
STATIC_ASSERT_EQUAL(PagePointer<4>::SIZE_OF_POINTED_MEMORY, PAGE_SIZE * 512LL * 512 * 512)

} /* namespace kernel */

#endif /* KERNEL_ARCH_PAGE_POINTER_H_INCLUDED */
