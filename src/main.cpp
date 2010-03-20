#include "Message.h"
#include "cxx/initCxxSupport.h"
#include "arch/GlobalDescriptorTable.h"
#include "arch/InterruptDescriptorTable.h"
#include "ut/framework/UnitTesting.h"
#include "cxx/rtti.h"
#include "arch/X64Constant.h"
#include "mm/PagePointer.h"
#include "mm/PageMap.h"
#include "mm/PageTable.h"
#include "mm/GenericAllocator.h"
#include "exe/SimpleLoader.h"
#include "arch/Processor.h"
#include "thread/UserAddressSpace.h"
#include "thread/Thread.h"

namespace kernel {

// Defined in ld script
extern "C" int __ld_image_end, __ld_image_start;

extern "C" int sampleServer;
void main() {
	Message::brief << "Welcome to the hell!\n";
	Message::brief << "__ld_image_start: " << &__ld_image_start << "\n"
			<< "__ld_image_end:   " << &__ld_image_end << "\n";

	getSingleInstance<GlobalDescriptorTable>().load();
	getSingleInstance<InterruptDescriptorTable>().load();
	getSingleInstance<Processor>().initialize();

	SimpleLoader loader;
	loader.parse(&sampleServer, 0);
	Address base = loader.getBaseAddress();
	Size size = loader.getMemoryImageSize();
	UserAddressSpace* addressSpace = new UserAddressSpace(size);
	addressSpace->activate();
	Address entry = loader.load((void*)base, size);
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
	PageMap::reload();

	WAIT_FOR_DEBUGGER();

	initCxxSupport();

	main();
}
