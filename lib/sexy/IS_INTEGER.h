#ifndef KERNEL_SEXY_IS_INTEGER_H_INCLUDED
#define KERNEL_SEXY_IS_INTEGER_H_INCLUDED

namespace kernel {

template<typename T> class IS_INTEGER {
public:
	enum {
		value = 0
	};
};

#ifdef SPECIALIZE_IS_INTEGER_VALUE
#error "SPECIALIZE_IS_INTEGER_VALUE is already defined"
#else
#define SPECIALIZE_IS_INTEGER_VALUE(type) \
	template<> class IS_INTEGER<type> { \
	public: \
		enum { \
			value = 1 \
		}; \
	}
#endif

SPECIALIZE_IS_INTEGER_VALUE(signed char);
SPECIALIZE_IS_INTEGER_VALUE(unsigned char);
SPECIALIZE_IS_INTEGER_VALUE(short);
SPECIALIZE_IS_INTEGER_VALUE(unsigned short);
SPECIALIZE_IS_INTEGER_VALUE(int);
SPECIALIZE_IS_INTEGER_VALUE(unsigned int);
SPECIALIZE_IS_INTEGER_VALUE(long);
SPECIALIZE_IS_INTEGER_VALUE(unsigned long);
SPECIALIZE_IS_INTEGER_VALUE(long long);
SPECIALIZE_IS_INTEGER_VALUE(unsigned long long);

#undef SPECIALIZE_IS_INTEGER_VALUE

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_INTEGER_H_INCLUDED */
