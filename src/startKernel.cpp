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

namespace kernel {

// Defined in ld script
extern "C" int __ld_image_end, __ld_image_start;

extern "C" int sampleServer;
void startKernel() {
	Message::brief << "__ld_image_start: " << &__ld_image_start << "\n"
			<< "__ld_image_end:   " << &__ld_image_end << "\n";
	getProcessorInstance<GlobalDescriptorTable>();
	getProcessorInstance<InterruptTable>();
	getProcessorInstance<Processor>().initialize();
	getProcessorInstance<InterruptController>();

	TestRunner& runner = getSingleInstance<TestRunner>();
	TestResult result;
	runner.run(result);
	result.show();

	SimpleLoader* loader = new SimpleLoader();
	loader->parse(&sampleServer, 0);
	Address base = loader->getBaseAddress();
	Size size = loader->getMemoryImageSize();
	AddressSpace* addressSpace = new AddressSpace(size);
	addressSpace->activate();
	Address entry = loader->load((void*)base, size);

	delete loader;

	Thread sample(entry);
	sample.start();

	// XXX Objects on the stack should be destructed
}

} /* namespace kernel */

#ifdef BUILD_DEBUG_MODE_KERNEL
static void WAIT_FOR_DEBUGGER() {
	volatile int go = 0;
	while (go == 0)
		;
}
#else
#	define WAIT_FOR_DEBUGGER()
#endif

extern "C" void startKernel() {
	using namespace kernel;

	// Remove the lower half of the page map, which can help us find out bugs
	PagePointer<4>* levelFour = (PagePointer<4>*)PageTable<4>::LOWEST_TABLE_ADDRESS;
	levelFour->present = 0;
	// Remove the temporary page map, so the space is available to kernel stack.
	PageMap::create(KERNEL_STACK_TOP, TEMP_MAP_SIZE, 0, true);

	WAIT_FOR_DEBUGGER();

	initCxxSupport();

	::kernel::startKernel();
}
