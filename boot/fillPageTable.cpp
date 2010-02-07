typedef unsigned long long PageTableItem;

/**
 * Fill temporary page table.
 * Map the lowest 2M, whether the memory really exists or not.
 *
 * @return The address of Page Map Level 4
 */
extern "C" unsigned long fillPageTable() {
	enum {
		MEMORY_SIZE = 2 * 1024 * 1024,
		MAP_START = 1024 * 1024,
		PAGE_SIZE = 1024 * 4,
		PAGE_MASK = 0xfffff000,
		ATTRIBUTE = (1 << 0) /* P  Page presents */
					| (1 << 1) /* R/W Read & write access */
	};

	unsigned long offset = MAP_START;
	PageTableItem* pageTable = (PageTableItem*)offset;
	for (unsigned int i = 0; i < MEMORY_SIZE / PAGE_SIZE; ++i) {
		pageTable[i] = (i * PAGE_SIZE) | ATTRIBUTE;
	}
	offset += PAGE_SIZE;

	PageTableItem* pageDirectory = (PageTableItem*)offset;
	pageDirectory[0] = ((long)pageTable & PAGE_MASK) | ATTRIBUTE;
	for (int i = 1; i < 512; ++i) {
		pageDirectory[i] = 0;
	}
	offset += PAGE_SIZE;

	PageTableItem* pagePointer = (PageTableItem*)offset;
	pagePointer[0] = ((long)pageDirectory & PAGE_MASK) | ATTRIBUTE;
	for (int i = 1; i < 512; ++i) {
		pagePointer[i] = 0;
	}
	offset += PAGE_SIZE;

	PageTableItem* pageMap = (PageTableItem*)offset;
	pageMap[0] = ((long)pagePointer & PAGE_MASK) | ATTRIBUTE;
	for (int i = 1; i < 512; ++i) {
		pageMap[i] = 0;
	}
	pageMap[510] = pageMap[0]; /* Higher half */
	pageMap[511] = ((long)pageMap & PAGE_MASK) | ATTRIBUTE; /* self reference */

	return offset;
}

