#ifndef KERNEL_CONFIG_H_INCLUDED
#define KERNEL_CONFIG_H_INCLUDED

namespace kernel {

// XXX Thread safety
class Config {
	~Config();

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

} // KERNEL_CONFIG_H_INCLUDED

#endif // KERNEL_CONFIG_H_INCLUDED
