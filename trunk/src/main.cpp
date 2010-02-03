#include "Printer.h"
#include "cxx/initCxxSupport.h"
#include "arch/GlobalDescriptorTable.h"
#include "arch/InterruptDescriptorTable.h"
#include "ut/framework/UnitTesting.h"
#include "System.h"
#include "cxx/rtti.h"

namespace kernel {

void main() {
	Printer& console = getSingleInstance<Printer>();

	console << "Welcome\n";
	console << "to the hell!\n";

	getSingleInstance<GlobalDescriptorTable>().load();
	getSingleInstance<InterruptDescriptorTable>().load();

	console << "IDT works now\n";

	TestRunner& runner = getSingleInstance<TestRunner>();

	runner.verbose();
	TestResult result;
	runner.run(result);
	result.show();
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

	initCxxSupport();

	main();

	System::halt();
}
