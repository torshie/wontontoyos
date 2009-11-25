#ifndef __WONTON_SEXY_IS_INTEGER_H_INCLUDED__
#define __WONTON_SEXY_IS_INTEGER_H_INCLUDED__

namespace sexy {

template<typename T>
class IS_INTEGER {
public:
	enum {
		value = 0
	};
};

#define __SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(type) \
	template<> \
	class IS_INTEGER<type> { \
	public: \
		enum { \
			value = 1 \
		}; \
	}

__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(signed char);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(unsigned char);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(short);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(unsigned short);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(int);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(unsigned int);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(long);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(unsigned long);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(long long);
__SEXY_SPECIALIZE_IS_INTEGER_OPERATOR_BOOL(unsigned long long);

} /* namespace sexy */

#endif
