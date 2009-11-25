#include "Printer.h"
#include <cxx/initCxxSupport.h>
#include "arch/GlobalDescriptorTable.h"

using namespace base;

namespace kernel {

void main() {
	Printer& console = getSingleInstance<Printer>();

	console << "Welcome\n";
	console << "to the hell!\n";

	getSingleInstance<GlobalDescriptorTable>().load();

	console << "Ah, we are still alive!\n";
}

} /* namespace kernel */

extern "C" void startKernel() {
	using namespace kernel;

	/**
	 * Remove the lower half of the page map, which can help us find out
	 * bugs
	 *
	 * XXX This is extremely ugly
	 */
	U64* levelFour = (U64*)0xFFFFFFFFFFFFF000;
	levelFour[0] = 0;
	Address physical = levelFour[511] & 0xFFFFFFFFFFFFF000;
	asm volatile("mov %0, %%cr3" : : "r"(physical));

	cxx::initCxxSupport();

	main();

	for (;;)
		;
}
