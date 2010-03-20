#ifndef KERNEL_MESSAGE_H_INCLUDED
#define KERNEL_MESSAGE_H_INCLUDED

#include "Printer.h"
#include "Property.h"

namespace kernel {

// XXX Thread safety
class Message {
private:
	explicit Message(int s) : console(getSingleInstance<Printer>()), severity(s) {}
	Message(const Message&);
	const Message& operator = (const Message&);

public:
	enum __ {
		DEBUG = 1, VERBOSE, INFO, BRIEF, WARNING, ERROR, CRITICAL, FATAL
	};

	static Message debug, verbose, info, brief, warning, error, critical, fatal;

	template<typename T> Message& operator << (const T& data);

private:
	Printer& console;
	int severity;
};

template<typename T> Message& Message::operator << (const T& data) {
	int hideMessage = Property::get<Property::MISC_HIDE_MESSAGE, int>();
	if (severity > hideMessage) {
		console << data;
	}
	return *this;
}

} // namespace kernel

#endif // KERNEL_MESSAGE_H_INCLUDED
