#ifndef __WONTON_SEXY_IS_VOID_H_INCLUDED__
#define __WONTON_SEXY_IS_VOID_H_INCLUDED__

namespace sexy {

template<typename T>
class IS_VOID {
public:
	enum {
		value = 0
	};
};

template<>
class IS_VOID<void> {
public:
	enum {
		value = 1
	};
};

} /* namespace sexy */

#endif
