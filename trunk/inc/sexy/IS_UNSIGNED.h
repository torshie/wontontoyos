#ifndef KERNEL_SEXY_IS_UNSIGNED_H_INCLUDED
#define KERNEL_SEXY_IS_UNSIGNED_H_INCLUDED

#include <sexy/IS_SIGNED.h>
#include <sexy/IS_INTEGER.h>

namespace kernel {

template<typename Primitive>
class IS_UNSIGNED {
public:
	enum {
		value = IS_INTEGER<Primitive>::value ?
					(!IS_SIGNED<Primitive>::value) : 0
	};
};

} /* namespace kernel */

#endif /* KERNEL_SEXY_IS_UNSIGNED_H_INCLUDED */
