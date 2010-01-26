#include <generic/Memory.h>
#include <generic/type.h>

namespace kernel {

/**
 * XXX Optimize
 */
void Memory::memcpy(void* dst, const void* src, Size size) {
	for (Size i = 0; i < size; ++i) {
		((char*)dst)[i] = ((char*)src)[i];
	}
}

/**
 * XXX Optimize
 */
void Memory::zeroize(void* dst, Size size) {
	memset(dst, 0, size);
}

/**
 * XXX Optimize
 */
void Memory::memset(void* dst, char value, Size count) {
	for (Size i = 0; i < count; ++i) {
		((char*)dst)[i] = value;
	}
}

/**
 * XXX Optimize
 */
int Memory::strcmp(const char* first, const char* second) {
	const unsigned char* a = (const unsigned char*)first;
	const unsigned char* b = (const unsigned char*)second;
	for (; *a && *b; ++a, ++b) {
		if (*a != *b) {
			return *a - *b;
		}
	}
	return *a - *b;
}

} /* namespace kernel */
