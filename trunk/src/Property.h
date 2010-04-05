#ifndef KERNEL_PROPERTY_H_INCLUDED
#define KERNEL_PROPERTY_H_INCLUDED

namespace kernel {

class Property {
	~Property();

	template<int KEY, typename Value> class Attribute {
		~Attribute();

	public:
		static Value get();
		static void set(const Value& value);

	private:
		static Value storage;
	};

public:
	enum __ {
		MISC_HIDE_MESSAGE = 10000,

		PROCESS_ACTIVE_ADDRESS_SPACE = 20000,

		THREAD_STACK_SPACE_SIZE = 30000,
	};

	template<int KEY, typename Value> static Value get() {
		return Attribute<KEY, Value>::get();
	}

	template<int KEY, typename Value> static void set(const Value& value) {
		Attribute<KEY, Value>::set(value);
	}
};

} // namespace kernel

#endif // KERNEL_PROPERTY_H_INCLUDED
