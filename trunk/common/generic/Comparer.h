#ifndef KERNEL_GENERIC_COMPARER_H_INCLUDED
#define KERNEL_GENERIC_COMPARER_H_INCLUDED

#include <generic/Utils.h>
#include <sexy/TYPE_SELECTOR.h>
#include <sexy/IS_STRING.h>
#include <sexy/IS_ENUM.h>
#include <sexy/IS_POINTER.h>

namespace kernel {

template<typename Left, typename Right> class Comparer {
	class OldStringComparer {
	public:
		static bool equal(const char* a, const char* b) {
			return Utils::strcmp(a, b) == 0;
		}

		static bool less(const char* a, const char* b) {
			return Utils::strcmp(a, b) < 0;
		}
	};

	template<typename L, typename R> class PointerComparer {
	public:
		static bool equal(L left, R right) {
			return (Address)left == (Address)right;
		}

		static bool less(L left, R right) {
			return (Address)left < (Address)right;
		}
	};

	template<typename L, typename R> class OperatorComparer {
	public:
		static bool equal(const L& left, const R& right) {
			return left == right;
		}

		static bool less(const L& left, const R& right) {
			return left < right;
		}
	};

	template<typename Integer> class IntegerComparer {
	public:
		static bool equal(const Integer& left, const Integer& right) {
			return left == right;
		}

		static bool less(const Integer& left, const Integer& right) {
			return left < right;
		}
	};

	typedef typename TYPE_SELECTOR<IS_STRING<Left>::value,
		OldStringComparer,
		typename TYPE_SELECTOR<(IS_POINTER<Left>::value || IS_POINTER<Right>::value),
			PointerComparer<Left, Right>,
			typename TYPE_SELECTOR<(IS_INTEGER<Right>::value && IS_INTEGER<Right>::value),
				typename TYPE_SELECTOR<(sizeof(Left) > sizeof(Right)),
					IntegerComparer<Left>,
					IntegerComparer<Right>
				>::Type,
				OperatorComparer<Left, Right>
			>::Type
		>::Type
	>::Type CompetentComparer;

public:
	static bool equal(const Left& left, const Right& right) {
		return CompetentComparer::equal(left, right);
	}

	static bool less(const Left& left, const Right& right) {
		return CompetentComparer::less(left, right);
	}

	static bool unequal(const Left& left, const Right& right) {
		return !equal(left, right);
	}
};

} // namespace kernel

#endif // KERNEL_GENERIC_COMPARER_H_INCLUDED
