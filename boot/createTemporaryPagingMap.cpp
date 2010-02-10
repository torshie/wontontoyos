#include "arch/X64Constant.h"
#include <kernel/abi.h>
#include "mm/PagePointer.h"

using namespace kernel;

/**
 * Create a temporary paging map.
 *
 * @return The address of Page Map Level 4
 */
/**
 * XXX We cannot link this file against other part of kernel source files, even when they are
 * compiled into 32-bit object files. Find out why, and then remove all the duplications in
 * this file.
 */
extern "C" Offset createTemporaryPagingMap() {
	enum {
		NUMBER_OF_LEVEL_TWO_PAGE_POINTERS = 2,
		NUMBER_OF_LEVEL_THREE_PAGE_POINTERS = 1,
		NUMBER_OF_LEVEL_FOUR_PAGE_POINTERS = 1,
		SIZE_OF_MAPPED_MEMORY = PagePointer<2>::SIZE_OF_POINTED_MEMORY
									* NUMBER_OF_LEVEL_TWO_PAGE_POINTERS,
		PAGING_MAP_SIZE = (NUMBER_OF_LEVEL_TWO_PAGE_POINTERS
							+ NUMBER_OF_LEVEL_THREE_PAGE_POINTERS
							+ NUMBER_OF_LEVEL_FOUR_PAGE_POINTERS + 1) * PAGE_SIZE
	};

	for (Offset i = KERNEL_RESERVED_MEMORY; i < PAGING_MAP_SIZE; ++i) {
		*(char*)(KERNEL_RESERVED_MEMORY + i) = 0;
	}

	Offset offset = KERNEL_RESERVED_MEMORY;
	PagePointer<1>* levelOne = (PagePointer<1>*)offset;
	for (unsigned int i = 0; i < SIZE_OF_MAPPED_MEMORY / PAGE_SIZE; ++i) {
		if (i < KERNEL_RESERVED_MEMORY / PAGE_SIZE
				|| i >= (KERNEL_RESERVED_MEMORY + KERNEL_TEMP_AREA) / PAGE_SIZE) {
			(levelOne + i)->present = 1;
		}
		(levelOne + i)->writable = 1;
		(levelOne + i)->page = i;
	}
	offset += PAGE_SIZE * NUMBER_OF_LEVEL_TWO_PAGE_POINTERS;

	PagePointer<2>* levelTwo = (PagePointer<2>*)offset;
	for (int i = 0; i < NUMBER_OF_LEVEL_TWO_PAGE_POINTERS; ++i) {
		levelTwo[i].physicalAddress = (Address)levelOne + PAGE_SIZE * i;
		levelTwo[i].writable = 1;
		levelTwo[i].present = 1;
	}
	offset += PAGE_SIZE * NUMBER_OF_LEVEL_THREE_PAGE_POINTERS;

	PagePointer<3>* levelThree = (PagePointer<3>*)offset;
	levelThree[0].physicalAddress = (Address)levelTwo;
	levelThree[0].present = 1;
	levelThree[0].writable = 1;
	offset += PAGE_SIZE * NUMBER_OF_LEVEL_FOUR_PAGE_POINTERS;

	/**
	 * Identity mapping the kernel
	 */
	PagePointer<4>* levelFour = (PagePointer<4>*)offset;
	levelFour[0].physicalAddress = (Address)levelThree;
	levelFour[0].present = 1;
	levelFour[0].writable = 1;

	/**
	 * While identity mapping, we also map the kernel to higher half
	 */
	enum {
		SIZE_OF_SPACE_ABOVE_BASE_ADDRESS = -KERNEL_VIRTUAL_BASE,
		RIGHT_TO_LEFT_INDEX = SIZE_OF_SPACE_ABOVE_BASE_ADDRESS
									/ PagePointer<4>::SIZE_OF_POINTED_MEMORY,
		LEFT_TO_RIGHT_INDEX = PagePointer<4>::NUMBER_OF_POINTERS_PER_PAGE - RIGHT_TO_LEFT_INDEX
	};
	levelFour[LEFT_TO_RIGHT_INDEX].physicalAddress = (Address)levelThree;
	levelFour[LEFT_TO_RIGHT_INDEX].present = 1;
	levelFour[LEFT_TO_RIGHT_INDEX].writable = 1;

	enum {
		SELF_REFERENCE_ENTRY = PagePointer<4>::NUMBER_OF_POINTERS_PER_PAGE - 1
	};
	levelFour[SELF_REFERENCE_ENTRY].physicalAddress = (Address)levelFour;
	levelFour[SELF_REFERENCE_ENTRY].present = 1;
	levelFour[SELF_REFERENCE_ENTRY].writable = 1;

	return offset;
}

