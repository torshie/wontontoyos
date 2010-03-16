#ifndef KERNEL_MESSAGE_H_INCLUDED
#define KERNEL_MESSAGE_H_INCLUDED

#include "Printer.h"
#include "SpecializeConfig.h"

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

class Config;
template<int KEY, typename Value> void Config::get(Value& value);

template<typename T> Message& Message::operator << (const T& data) {
	int hideMessage;
	Config::get<Config::Misc::HIDE_MESSAGE>(hideMessage);
	if (severity > hideMessage) {
		console << data;
	}
	return *this;
}

} // namespace kernel

#endif // KERNEL_MESSAGE_H_INCLUDED