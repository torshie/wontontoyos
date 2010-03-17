#ifndef KERNEL_THREAD_THREAD_H_INCLUDED
#define KERNEL_THREAD_THREAD_H_INCLUDED

namespace kernel {

class Thread {
public:
	void start();
	void resume();
	void kill();
};

} // namespace kernel

#endif // KERNEL_THREAD_THREAD_H_INCLUDED
