#ifndef KERNEL_SYSTEM_H_INCLUDED
#define KERNEL_SYSTEM_H_INCLUDED

namespace kernel {

class System {
public:
	// XXX Halt the CPU instead of looping forever
	static void halt() {
		for (;;)
			;
	}
};

} // namespace kernel

#endif // KERNEL_SYSTEM_H_INCLUDED
