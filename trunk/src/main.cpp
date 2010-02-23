#include "Printer.h"
#include "cxx/initCxxSupport.h"
#include "arch/GlobalDescriptorTable.h"
#include "arch/InterruptDescriptorTable.h"
#include "ut/framework/UnitTesting.h"
#include "System.h"
#include "cxx/rtti.h"
#include "arch/X64Constant.h"
#include "mm/PagePointer.h"
#include "mm/PageMap.h"
#include "mm/PageTable.h"

namespace kernel {

extern "C" int __ld_bss_end;
void main() {
	Printer& console = getSingleInstance<Printer>();

	console << "Welcome\n";
	console << "to the hell!\n";

	getSingleInstance<GlobalDescriptorTable>().load();
	getSingleInstance<InterruptDescriptorTable>().load();

	TestRunner& runner = getSingleInstance<TestRunner>();
	runner.verbose();
	TestResult result;
	runner.run(result);
	result.show();

	console << "__ld_bss_end: " << &__ld_bss_end << "\n";
}

} /* namespace kernel */

extern "C" void startKernel() {
	using namespace kernel;

	// Remove the lower half of the page map, which can help us find out bugs
	PagePointer<4>* levelFour = (PagePointer<4>*)PageTable<4>::LOWEST_TABLE_ADDRESS;
	levelFour->present = 0;
	PageMap::reload();

	initCxxSupport();

	main();

	System::halt();
}