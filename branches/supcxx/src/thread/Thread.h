#ifndef KERNEL_THREAD_THREAD_H_INCLUDED
#define KERNEL_THREAD_THREAD_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class Thread {
public:
	explicit Thread(Address e) : entry(e) {}

	void start() __attribute__((__noreturn__));
	void resume();
	void kill();

private:
	Address entry;
};

} // namespace kernel

#endif // KERNEL_THREAD_THREAD_H_INCLUDED
