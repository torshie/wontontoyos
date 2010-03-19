#include "Config.h"
#include "Message.h"

namespace kernel {

template<int KEY, typename Value> Value Config::Attribute<KEY, Value>::get() {
	return storage;
}

template<int KEY, typename Value> void Config::Attribute<KEY, Value>::set(const Value& value) {
	storage = value;
}

#ifndef INSTANTIATE_CONFIG_ATTRIBUTE
#	define INSTANTIATE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue) \
		template class Config::Attribute<KEY, Type>; \
		template<> Type Config::Attribute<KEY, Type>::storage = defaultValue
#else
#	error "INSTANTIATE_CONFIG_ATTRIBUTE is already defined"
#endif

INSTANTIATE_CONFIG_ATTRIBUTE(Config::Misc::HIDE_MESSAGE, int, Message::INFO);

} // namespace kernel
