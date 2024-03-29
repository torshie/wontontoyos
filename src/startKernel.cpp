#include "Message.h"
#include "cxx/initCxxSupport.h"
#include "arch/GlobalDescriptorTable.h"
#include "arch/InterruptTable.h"
#include "ut/framework/UnitTesting.h"
#include "cxx/rtti.h"
#include "arch/X64Constant.h"
#include "mm/PagePointer.h"
#include "mm/PageMap.h"
#include "mm/PageTable.h"
#include "mm/GenericAllocator.h"
#include "exe/SimpleLoader.h"
#include "arch/Processor.h"
#include "arch/getProcessorInstance.h"
#include "thread/AddressSpace.h"
#include "thread/Thread.h"
#include "ut/framework/UnitTesting.h"
#include "arch/InterruptController.h"
#include "arch/InputOutputController.h"
#include "Property.h"
#include "driver/timer/RealTimeClock/RealTimeClock.h"

namespace kernel {

// Defined in ld script
extern "C" int __ld_image_end, __ld_image_start;

extern "C" int sampleServer;
void startKernel(Address timerAddress) {
	Property::set<Property::PARAM_EVENT_TIMER_BASE>(timerAddress);

	Message::brief << "__ld_image_start: " << &__ld_image_start << "\n"
			<< "__ld_image_end:   " << &__ld_image_end << "\n";
	Message::brief << "Timer Address: " << timerAddress << "\n";
	getProcessorInstance<GlobalDescriptorTable>();
	getProcessorInstance<InterruptTable>();
	getProcessorInstance<InterruptController>();
	getSingleInstance<RealTimeClock>();
	InputOutputController& io = getSingleInstance<InputOutputController>();

	Message::brief << "IOAPIC Version: " << io.getRegister(InputOutputController::REG_VERSION)
			<< "\n";

	TestRunner& runner = getSingleInstance<TestRunner>();
	TestResult result;
	runner.run(result);
	result.show();
	asm volatile("sti");
}

} /* namespace kernel */

#ifdef ENABLE_GDB_HOOK
static void WAIT_FOR_GDB() {
	volatile int go = 0;
	while (go == 0)
		;
}
#else
#	define WAIT_FOR_GDB()
#endif

using namespace kernel;

extern "C" void startKernel(Address timerAddress) {

	// Remove the lower half of the page map, which can help us find out bugs
	PagePointer<4>* levelFour = (PagePointer<4>*)PageTable<4>::LOWEST_TABLE_ADDRESS;
	levelFour->present = 0;
	// Remove lower address mapping of paging map, so the space is available to kernel stack.
	PageMap::create(KERNEL_STACK_TOP, TEMP_MAP_SIZE, 0, true);

	WAIT_FOR_GDB();

	initCxxSupport();
	::kernel::startKernel(timerAddress);

	for (;;);
}
