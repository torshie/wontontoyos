#include "UserAddressSpace.h"
#include "mm/PageMap.h"
#include "mm/PageTable.h"

namespace kernel {

UserAddressSpace::UserAddressSpace(Size basicSpaceSize, bool activateImmediately) {
	Size stackSize = Property::get<Property::THREAD_STACK_SPACE_SIZE, Size>();
	stackSpaceStart = USER_STACK_BOTTOM - stackSize;
	basicSpaceEnd = USER_VIRTUAL_BASE + basicSpaceSize;

	PageMap::create(USER_VIRTUAL_BASE, basicSpaceSize);
	PageMap::create(stackSpaceStart, stackSize);
	PagePointer<4>* basic = PagePointer<4>::getPointerTo(USER_VIRTUAL_BASE);
	PagePointer<4>* stack = PagePointer<4>::getPointerTo(stackSpaceStart);

	basicSpacePointer = *basic;
	stackSpacePointer = *stack;

	if (!activateImmediately) {
		UserAddressSpace* active =
				Property::get<Property::PROCESS_ACTIVE_ADDRESS_SPACE, UserAddressSpace*>();
		if (active != 0) {
			active->activate();
		}
	}
}

void UserAddressSpace::activate() {
	UserAddressSpace* active =
			Property::get<Property::PROCESS_ACTIVE_ADDRESS_SPACE, UserAddressSpace*>();
	if (active != this) {
		PagePointer<4>* basic = PagePointer<4>::getPointerTo(USER_VIRTUAL_BASE);
		PagePointer<4>* stack = PagePointer<4>::getPointerTo(stackSpaceStart);
		*basic = basicSpacePointer;
		*stack = stackSpacePointer;
		PageMap::reload();

		Property::set<Property::PROCESS_ACTIVE_ADDRESS_SPACE>(this);
	}
}

} // namespace kernel
