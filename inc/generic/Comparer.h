#ifndef KERNEL_GENERIC_COMPARER_H_INCLUDED
#define KERNEL_GENERIC_COMPARER_H_INCLUDED

#include <generic/Memory.h>
#include <sexy/TYPE_SELECTOR.h>
#include <sexy/IS_STRING.h>

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
	static bool equal(const Left& first, const Right& second) {
		return first == second;
	}
};

} /* namespace internal */

template<typename Left, typename Right>
class Comparer {
	typedef typename TYPE_SELECTOR<IS_STRING<Left>::value,
				internal::OldStringComparer,
				internal::OperatorComparer<Left, Right>
			>::Type InternalCompare;
public:
	static bool equal(const Left& left, const Right& right) {
		return InternalCompare::equal(left, right);
	}

	static bool unequal(const Left& left, const Right& right) {
		return !equal(left, right);
	}
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_COMPARER_H_INCLUDED */
