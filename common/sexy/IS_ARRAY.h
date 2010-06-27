#ifndef KERNEL_SEXY_IS_ARRAY_H_INCLUDED
#define KERNEL_SEXY_IS_ARRAY_H_INCLUDED

#include <generic/type.h>

namespace kernel {

template<typename T> class IS_ARRAY {
public:
	enum {
		value = 0
	};
};

template<typename T, Size N> class IS_ARRAY<T[N]> {
public:
	enum {
		value = 1
	};
};

template<typename T> class IS_ARRAY<T[0]> {
public:
	enum {
		value = 1
	};
};

template<typename T> class IS_ARRAY<T[]> {
public:
	enum {
		value = 1
	};
};

} // namespace kernel

#endif
