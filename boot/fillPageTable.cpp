#include "arch/X64Constant.h"
#include <kernel/abi.h>
#include "mm/PagePointer.h"
#include <cxx/new.h>

using namespace kernel;

typedef unsigned long long PageTableItem;

/**
 * Fill temporary page table.
 * Map the lowest 2M, whether the memory really exists or not.
 *
 * @return The address of Page Map Level 4
 */
/**
 * XXX DRY
 */
extern "C" unsigned long fillPageTable() {
	enum {
		PAGE_MAP_SIZE = PagePointer<2>::SIZE_OF_POINTED_MEMORY,
		PAGE_MAP_BEGIN = 1024 * 1024,
	};

	/**
	 * XXX Use Memory::memset() instead of loop
	 */
	for (Size i = PAGE_MAP_BEGIN; i < PAGE_MAP_BEGIN + PAGE_SIZE * 4; ++i) {
		*(char*)(PAGE_MAP_BEGIN + i) = 0;
	}

	Offset offset = PAGE_MAP_BEGIN;
	PagePointer<1>* levelOne = (PagePointer<1>*)offset;
	for (unsigned int i = 0; i < PAGE_MAP_SIZE / PAGE_SIZE; ++i) {
		(levelOne + i)->present = 1;
		(levelOne + i)->writable = 1;
		(levelOne + i)->page = i;
	}
	offset += PAGE_SIZE;

	PagePointer<2>* levelTwo = (PagePointer<2>*)offset;
	levelTwo[0].physicalAddress = (Address)levelOne;
	levelTwo[0].present = 1;
	levelTwo[0].writable = 1;
	offset += PAGE_SIZE;

	PagePointer<3>* levelThree = (PagePointer<3>*)offset;
	levelThree[0].physicalAddress = (Address)levelTwo;
	levelThree[0].present = 1;
	levelThree[0].writable = 1;
	offset += PAGE_SIZE;

	PagePointer<4>* levelFour = (PagePointer<4>*)offset;
	levelFour[0].physicalAddress = (Address)levelThree;
	levelFour[0].present = 1;
	levelFour[0].writable = 1;

	/**
	 * XXX Use copy-constructor instead
	 */
	levelFour[510].physicalAddress = (Address)levelThree; /* Higher half */
	levelFour[510].present = 1;
	levelFour[510].writable = 1;

	/**
	 * Self-reference
	 */
	levelFour[511].physicalAddress = (Address)levelFour;
	levelFour[511].present = 1;
	levelFour[511].writable = 1;

	return offset;
}

