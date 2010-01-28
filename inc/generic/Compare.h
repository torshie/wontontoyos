#ifndef KERNEL_GENERIC_COMPARE_H_INCLUDED
#define KERNEL_GENERIC_COMPARE_H_INCLUDED

#include <generic/Memory.h>

namespace kernel {

/**
 * XXX The code is ugly.
 */
template<typename Left, typename Right>
class Compare {
public:
	static bool equal(Left& left, Right& right) {
		return left == right;
	}

	static bool equal(const Left& left, const Right& right) {
		return left == right;
	}

	static bool equal(Left& left, const Right& right) {
		return left == right;
	}

	static bool equal(const Left& left, Right& right) {
		return left == right;
	}
};

#ifdef SPECIALIZE_COMPARE_EQUAL
#error "SPECIALIZE_COMPARE_EQUAL is already defined"
#else
#define SPECIALIZE_COMPARE_EQUAL \
	static bool equal(Left& left, Right& right) { \
		return Memory::strcmp(left, right) == 0; \
	} \
	\
	static bool equal(const Left& left, const Right& right) { \
		return Memory::strcmp(left, right) == 0; \
	} \
	\
	static bool equal(const Left& left, Right& right) { \
		return Memory::strcmp(left, right) == 0; \
	} \
	\
	static bool equal(Left& left, const Right& right) { \
		return Memory::strcmp(left, right) == 0; \
	}
#endif

template<typename Right>
class Compare<char*, Right> {
	typedef char* Left;
public:
	SPECIALIZE_COMPARE_EQUAL
};

template<int SIZE, typename Right>
class Compare<char[SIZE], Right> {
	typedef char Left[SIZE];
public:
	SPECIALIZE_COMPARE_EQUAL
};

#undef SPECIALIZE_COMPARE_EQUAL

} /* namespace kernel */

#endif /* KERNEL_GENERIC_COMPARE_H_INCLUDED */
