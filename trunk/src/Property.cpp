#include "Property.h"
#include "Message.h"

namespace kernel {

template<int KEY, typename Value> Value Property::Attribute<KEY, Value>::get() {
	return storage;
}

template<int KEY, typename Value> void Property::Attribute<KEY, Value>::set(const Value& value) {
	storage = value;
}

#define INSTANTIATE_PROPERTY_ATTRIBUTE(KEY, Type, defaultValue) \
	template class Property::Attribute<Property::KEY, Type>; \
	template<> Type Property::Attribute<Property::KEY, Type>::storage = defaultValue

INSTANTIATE_PROPERTY_ATTRIBUTE(MISC_HIDE_MESSAGE, int, Message::INFO);
INSTANTIATE_PROPERTY_ATTRIBUTE(THREAD_STACK_SPACE_SIZE, Size, 0x400000);
class AddressSpace;
INSTANTIATE_PROPERTY_ATTRIBUTE(PROCESS_ACTIVE_ADDRESS_SPACE, AddressSpace*, 0);
INSTANTIATE_PROPERTY_ATTRIBUTE(PARAM_EVENT_TIMER_BASE, Address, 0);

} // namespace kernel
