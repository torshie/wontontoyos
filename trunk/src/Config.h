#ifndef KERNEL_CONFIG_H_INCLUDED
#define KERNEL_CONFIG_H_INCLUDED

#include "MessageLevel.h"

namespace kernel {

// XXX Thread safety
class Config {
	Config();
	Config(const Config&);
	const Config& operator = (const Config&);

	template<int KEY, typename Value> class Attribute;
public:
	class Misc {
		enum __ {
			HIDE_MESSAGE
		};
	};

	template<int KEY, typename Value> static void get(Value& value) {
		Attribute<KEY, Value>::get(value);
	}

	template<int KEY, typename Value> static void set(const Value& value) {
		Attribute<KEY, Value>::set(value);
	}
};

#ifndef SPECIALIZE_CONFIG_ATTRIBUTE
#	ifdef KERNEL_IN_SRC_CONFIG_CPP
#		define INSTANTIATE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue) \
			Type Config::Attribute<KEY, Type>::storage = defaultValue
#	else
#		define INSTANTIATE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue)
#	endif
#	define SPECIALIZE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue) \
		template<> class Config::Attribute<KEY, Type > { \
			friend class Config; \
		private: \
			static void get(Type& value) { \
				value = storage; \
			} \
			static void set(const Type& value) { \
				storage = value; \
			} \
			static Type storage; \
		}; \
		INSTANTIATE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue)
#else
#	error "SPECIALIZE_CONFIG_ATTRIBUTE is already defined"
#endif

SPECIALIZE_CONFIG_ATTRIBUTE(Config::Misc::HIDE_MESSAGE, int, MessageLevel::INFO);

#undef SPECIALIZE_CONFIG_ATTRIBUTE

} // KERNEL_CONFIG_H_INCLUDED

#endif // KERNEL_CONFIG_H_INCLUDED
