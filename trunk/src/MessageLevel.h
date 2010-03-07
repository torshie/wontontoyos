#ifndef KERNEL_MESSAGE_LEVEL_H_INCLUDED
#define KERNEL_MESSAGE_LEVEL_H_INCLUDED

namespace kernel {

// XXX Define a class only for some constants, which is ugly!!!
class MessageLevel {
public:
	enum __ {
		DEBUG = 1, VERBOSE, INFO, BRIEF, WARNING, ERROR, CRITICAL, FATAL
	};
};

} // namespace kernel

#endif // KERNEL_MESSAGE_LEVEL_H_INCLUDED
