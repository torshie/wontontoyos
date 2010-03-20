#include "Property.h"
#include "Message.h"

namespace kernel {

template<int KEY, typename Value> Value Property::Attribute<KEY, Value>::get() {
	return storage;
}

template<int KEY, typename Value> void Property::Attribute<KEY, Value>::set(const Value& value) {
	storage = value;
}

#ifndef INSTANTIATE_PROPERTY_ATTRIBUTE
#	define INSTANTIATE_PROPERTY_ATTRIBUTE(KEY, Type, defaultValue) \
		template class Property::Attribute<KEY, Type>; \
		template<> Type Property::Attribute<KEY, Type>::storage = defaultValue
#else
#	error "INSTANTIATE_PROPERTY_ATTRIBUTE is already defined"
#endif

INSTANTIATE_PROPERTY_ATTRIBUTE(Property::MISC_HIDE_MESSAGE, int, Message::INFO);
INSTANTIATE_PROPERTY_ATTRIBUTE(Property::THREAD_STACK_SPACE_SIZE, Size, 0x400000);
class UserAddressSpace;
INSTANTIATE_PROPERTY_ATTRIBUTE(Property::PROCESS_ACTIVE_ADDRESS_SPACE, UserAddressSpace*, 0);

} // namespace kernel
