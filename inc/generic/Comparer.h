#ifndef KERNEL_GENERIC_COMPARER_H_INCLUDED
#define KERNEL_GENERIC_COMPARER_H_INCLUDED

#include <generic/Memory.h>
#include <sexy/TYPE_SELECTOR.h>
#include <sexy/IS_STRING.h>
#include <sexy/IS_ENUM.h>

namespace kernel {

namespace internal {

class OldStringComparer {
public:
	static bool equal(const char* a, const char* b) {
		return Memory::strcmp(a, b) == 0;
	}
};

template<typename Left, typename Right>
class OperatorComparer {
public:
	static bool equal(const Left& left, const Right& right) {
		return left == right;
	}
};

template<typename Left, typename Right>
class IntegerComparer {
public:
	static bool equal(U64 left, U64 right) {
		return left == right;
	}
};

} /* namespace internal */

template<typename Left, typename Right>
class Comparer {
	typedef typename TYPE_SELECTOR<IS_STRING<Left>::value,
				internal::OldStringComparer,
				typename TYPE_SELECTOR<(IS_ENUM<Left>::value || IS_ENUM<Right>::value),
					internal::IntegerComparer<Left, Right>,
					internal::OperatorComparer<Left, Right>
				>::Type >::Type InternalComparer;
public:
	static bool equal(const Left& left, const Right& right) {
		return InternalComparer::equal(left, right);
	}

	static bool unequal(const Left& left, const Right& right) {
		return !equal(left, right);
	}
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_COMPARER_H_INCLUDED */
