#ifndef KERNEL_GENERIC_COMPARER_H_INCLUDED
#define KERNEL_GENERIC_COMPARER_H_INCLUDED

#include <generic/Memory.h>
#include <sexy/TYPE_SELECTOR.h>
#include <sexy/IS_STRING.h>
#include <sexy/IS_ENUM.h>
#include <sexy/IS_POINTER.h>

namespace kernel {

template<typename Left, typename Right>
class Comparer {
	class OldStringComparer {
	public:
		static bool equal(const char* a, const char* b) {
			return Memory::strcmp(a, b) == 0;
		}
	};

	template<typename L, typename R>
	class PointerComparer {
	public:
		static bool equal(L l, R r) {
			return (Address)l == (Address)r;
		}
	};

	template<typename L, typename R>
	class OperatorComparer {
	public:
		static bool equal(const L& left, const R& right) {
			return left == right;
		}
	};
public:
	static bool equal(const Left& left, const Right& right) {
		typedef typename TYPE_SELECTOR<IS_STRING<Left>::value,
			OldStringComparer,
			typename TYPE_SELECTOR<(IS_POINTER<Left>::value || IS_POINTER<Right>::value),
				PointerComparer<Left, Right>,
				OperatorComparer<Left, Right>
			>::Type
		>::Type CompetentComparer;
		return CompetentComparer::equal(left, right);
	}

	static bool unequal(const Left& left, const Right& right) {
		return !equal(left, right);
	}
};

} /* namespace kernel */

#endif /* KERNEL_GENERIC_COMPARER_H_INCLUDED */
