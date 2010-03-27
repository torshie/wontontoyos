/**
 * XXX We cannot link this file against other kernel source files, even when they are
 * compiled into 32-bit object files. Find out why, and then remove all the duplications in
 * this file.
 */

#include "arch/X64Constant.h"
#include <kernel/abi.h>
#include "mm/PagePointer.h"

using namespace kernel;

enum {
	NUMBER_OF_LEVEL_TWO_PAGE_POINTERS = (TEMP_MAP_SIZE - 3 * PAGE_SIZE) / PAGE_SIZE,
	NUMBER_OF_LEVEL_THREE_PAGE_POINTERS = 1,
	NUMBER_OF_LEVEL_FOUR_PAGE_POINTERS = 1,
	SIZE_OF_MAPPED_MEMORY = PagePointer<2>::MEMORY_POINTED
									* NUMBER_OF_LEVEL_TWO_PAGE_POINTERS,
};

static void zeroize(void* memory, Size size) {
	char* p = (char*)memory;
	char* end = p + size;
	for (; p < end; ++p) {
		*p = 0;
	}
}

/**
 * Create a temporary identity & higher-half paging map.
 *
 * @return The address of Level Four Paging Map of the paging map
 */
static PagePointer<4>* createIdentityAndHigherHalfPagingMap() {
	Offset offset = LOW_MEMORY_SIZE;
	PagePointer<1>* levelOne = (PagePointer<1>*)offset;
	for (unsigned int i = 0; i < SIZE_OF_MAPPED_MEMORY / PAGE_SIZE; ++i) {
		if (i < LOW_MEMORY_SIZE / PAGE_SIZE
				|| i >= (LOW_MEMORY_SIZE + MEMORY_HOLE_SIZE) / PAGE_SIZE) {
			(levelOne + i)->present = 1;
		}
		(levelOne + i)->writable = 1;
		(levelOne + i)->page = i;
	}
	offset += PAGE_SIZE * NUMBER_OF_LEVEL_TWO_PAGE_POINTERS;

	PagePointer<2>* levelTwo = (PagePointer<2>*)offset;
	for (int i = 0; i < NUMBER_OF_LEVEL_TWO_PAGE_POINTERS; ++i) {
		levelTwo[i].address = (Address)levelOne + PAGE_SIZE * i;
		levelTwo[i].writable = 1;
		levelTwo[i].present = 1;
	}
	offset += PAGE_SIZE * NUMBER_OF_LEVEL_THREE_PAGE_POINTERS;

	PagePointer<3>* levelThree = (PagePointer<3>*)offset;
	levelThree[0].address = (Address)levelTwo;
	levelThree[0].present = 1;
	levelThree[0].writable = 1;
	offset += PAGE_SIZE * NUMBER_OF_LEVEL_FOUR_PAGE_POINTERS;

	PagePointer<4>* levelFour = (PagePointer<4>*)offset;
	levelFour[0].address = (Address)levelThree;
	levelFour[0].present = 1;
	levelFour[0].writable = 1;

	enum {
		SIZE_OF_SPACE_ABOVE_BASE_ADDRESS = -KERNEL_VIRTUAL_BASE,
		POINTERS_NEEDED = SIZE_OF_SPACE_ABOVE_BASE_ADDRESS / PagePointer<4>::MEMORY_POINTED,
		HIGHER_HALF_ENTRY = PagePointer<4>::POINTERS_PER_PAGE - POINTERS_NEEDED
	};
	levelFour[HIGHER_HALF_ENTRY].address = (Address)levelThree;
	levelFour[HIGHER_HALF_ENTRY].present = 1;
	levelFour[HIGHER_HALF_ENTRY].writable = 1;

	return levelFour;
}

/**
 * Create a temporary paging map.
 *
 * @return The address of Level Four Paging Map of the temporary paging map
 */
namespace pangu {

extern "C" PagePointer<4>* createTemporaryPagingMap() {
	// XXX Use kernel::Utils::zeroize instead
	zeroize((void*)(LOW_MEMORY_SIZE), TEMP_MAP_SIZE);

	PagePointer<4>* levelFour = createIdentityAndHigherHalfPagingMap();
	enum {
		SELF_REFERENCE_ENTRY = PagePointer<4>::POINTERS_PER_PAGE - 1
	};
	levelFour[SELF_REFERENCE_ENTRY].address = (Address)levelFour;
	levelFour[SELF_REFERENCE_ENTRY].present = 1;
	levelFour[SELF_REFERENCE_ENTRY].writable = 1;

	return levelFour;
}

} // namespace pangu
