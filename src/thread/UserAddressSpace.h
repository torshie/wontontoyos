#ifndef KERNEL_THREAD_USER_ADDRESS_SPACE_H_INCLUDED
#define KERNEL_THREAD_USER_ADDRESS_SPACE_H_INCLUDED

#include "mm/PagePointer.h"

namespace kernel {

class UserAddressSpace {
	UserAddressSpace(const UserAddressSpace&);
	const UserAddressSpace& operator = (const UserAddressSpace&);

public:
	explicit UserAddressSpace(Size basicSpaceSize, bool activateImmediately = true);

	// XXX Implement
	~UserAddressSpace() {}

	void activate();

private:
	PagePointer<4> basicSpacePointer;
	PagePointer<4> stackSpacePointer;
	Address basicSpaceEnd;
	Address stackSpaceStart;
};

} // namespace kernel

#endif // KERNEL_THREAD_USER_ADDRESS_SPACE_H_INCLUDED
