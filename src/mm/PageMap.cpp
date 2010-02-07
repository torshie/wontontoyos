#include "PageMap.h"
#include "PageTable.h"
#include "arch/X64Constant.h"
#include <kernel/abi.h>
#include "debug.h"

namespace kernel {

void PageMap::reload() {
	PageTable<4>* table = (PageTable<4>*)(PageTable<4>::BASE_ADDRESS);
	Address physicalAddress = table->pointer[PageTable<4>::POINTERS_PER_TABLE - 1].page
										* PAGE_SIZE;
	asm volatile("mov %0, %%cr3" : : "r"(physicalAddress));
}

}


 /* namespace kernel */
