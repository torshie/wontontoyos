#ifndef __WONTON_SEXY_IS_SIGNED_H_INCLUDED__
#define __WONTON_SEXY_IS_SIGNED_H_INCLUDED__

namespace sexy {

template<typename Primitive>
class IS_SIGNED {
public:
	enum {
		value = 0
	};
};

#define __SEXY_SPECIALIZE_IS_SIGNED_OPERATOR_BOOL(type) \
	template<> \
	class IS_SIGNED<type> { \
	public: \
		enum { \
			value = 1 \
		}; \
	}

__SEXY_SPECIALIZE_IS_SIGNED_OPERATOR_BOOL(signed char);
__SEXY_SPECIALIZE_IS_SIGNED_OPERATOR_BOOL(short);
__SEXY_SPECIALIZE_IS_SIGNED_OPERATOR_BOOL(int);
__SEXY_SPECIALIZE_IS_SIGNED_OPERATOR_BOOL(long);
__SEXY_SPECIALIZE_IS_SIGNED_OPERATOR_BOOL(long long);

} /* namespace sexy */

#endif
