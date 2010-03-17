#ifndef KERNEL_SPECIALIZE_CONFIG_H_INCLUDED
#define KERNEL_SPECIALIZE_CONFIG_H_INCLUDED

#include "Config.h"

#ifndef SPECIALIZE_CONFIG_ATTRIBUTE
#	ifndef INSTANTIATE_CONFIG_ATTRIBUTE
#		ifdef KERNEL_IN_SRC_CONFIG_CPP
#			define INSTANTIATE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue) \
				Type Config::Attribute<KEY, Type>::storage = defaultValue
#		else
#			define INSTANTIATE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue)
#		endif
#	else
#		error "INSTANTIATE_CONFIG_ATTRIBUTE is already defined"
#	endif
#	define SPECIALIZE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue) \
		namespace kernel { \
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
			INSTANTIATE_CONFIG_ATTRIBUTE(KEY, Type, defaultValue); \
		} // namespace kernel

#else
#	error "SPECIALIZE_CONFIG_ATTRIBUTE is already defined"
#endif

#include "Message.h"
SPECIALIZE_CONFIG_ATTRIBUTE(Config::Misc::HIDE_MESSAGE, int, Message::INFO);

#undef SPECIALIZE_CONFIG_ATTRIBUTE

#endif // KERNEL_SPECIALIZE_CONFIG_H_INCLUDED
