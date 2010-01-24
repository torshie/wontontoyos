#ifndef KERNEL_SEXY_IS_SIGNED_H_INCLUDED
#define KERNEL_SEXY_IS_SIGNED_H_INCLUDED

namespace kernel {

template<typename Primitive>
class IS_SIGNED {
public:
	enum {
		value = 0
	};
};

#define KERNEL_SEXY_SPECIALIZE_IS_SIGNED_VALUE(type) \
	template<> \
	class IS_SIGNED<type> { \
	public: \
		enum { \
			value = 1 \
		}; \
	}

KERNEL_SEXY_SPECIALIZE_IS_SIGNED_VALUE(signed char);
KERNEL_SEXY_SPECIALIZE_IS_SIGNED_VALUE(short);
KERNEL_SEXY_SPECIALIZE_IS_SIGNED_VALUE(int);
KERNEL_SEXY_SPECIALIZE_IS_SIGNED_VALUE(long);
KERNEL_SEXY_SPECIALIZE_IS_SIGNED_VALUE(long long);

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_SIGNED_H_INCLUDED */
