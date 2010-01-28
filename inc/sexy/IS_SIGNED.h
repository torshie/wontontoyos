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

#ifdef SPECIALIZE_IS_SIGNED_VALUE
#error "SPECIALIZE_IS_SIGNED_VALUE is already defined"
#else
#define SPECIALIZE_IS_SIGNED_VALUE(type) \
	template<> \
	class IS_SIGNED<type> { \
	public: \
		enum { \
			value = 1 \
		}; \
	}
#endif

SPECIALIZE_IS_SIGNED_VALUE(signed char);
SPECIALIZE_IS_SIGNED_VALUE(short);
SPECIALIZE_IS_SIGNED_VALUE(int);
SPECIALIZE_IS_SIGNED_VALUE(long);
SPECIALIZE_IS_SIGNED_VALUE(long long);

#undef SPECIALIZE_IS_SIGNED_VALUE

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_SIGNED_H_INCLUDED */
