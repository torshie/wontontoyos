#ifndef KERNEL_THREAD_ADDRESS_SPACE_H_INCLUDED
#define KERNEL_THREAD_ADDRESS_SPACE_H_INCLUDED

#include "mm/PagePointer.h"

namespace kernel {

class AddressSpace {
	AddressSpace(const AddressSpace&);
	const AddressSpace& operator = (const AddressSpace&);

public:
	explicit AddressSpace(Size basicSpaceSize, bool activateImmediately = true);

	// XXX Implement
	~AddressSpace() {}

	void activate();

private:
	PagePointer<4> basicSpacePointer;
	PagePointer<4> stackSpacePointer;
	Address basicSpaceEnd;
	Address stackSpaceStart;
};

} // namespace kernel

#endif // KERNEL_THREAD_ADDRESS_SPACE_H_INCLUDED
