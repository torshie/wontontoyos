#ifndef __WONTON_SEXY_IS_UNSIGNED_H_INCLUDED__
#define __WONTON_SEXY_IS_UNSIGNED_H_INCLUDED__

#include <sexy/IS_SIGNED.h>
#include <sexy/IS_INTEGER.h>

namespace sexy {

template<typename Primitive>
class IS_UNSIGNED {
public:
	enum {
		value = IS_INTEGER<Primitive>::value ?
					(!IS_SIGNED<Primitive>::value) : 0
	};
};

} /* namespace sexy */

#endif
