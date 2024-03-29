#include <generic/Utils.h>
#include <generic/type.h>

namespace kernel {

// XXX Optimize
void Utils::memcpy(void* dst, const void* src, Size size) {
	for (Size i = 0; i < size; ++i) {
		((char*)(dst))[i] = ((char*)(src))[i];
	}
}

// XXX Optimize
void Utils::zeroize(void *dst, Size size) {
	memset(dst, 0, size);
}

// XXX Optimize
void Utils::memset(void *dst, char value, Size count) {
	for (Size i = 0; i < count; ++i) {
		((char*)(dst))[i] = value;
	}
}

// XXX Optimize
Size Utils::strncpy(char *dst, const char *src, Size space) {
	Size length = 0;
	char* end = dst + space;
	for (; *src && dst < end - 1; ++src, ++dst, ++length) {
		*dst = *src;
	}
	*dst = 0;
	return length;
}

// XXX Optimize
int Utils::strcmp(const char *first, const char *second, Size length) {
	if (length == 0) {
		return 0;
	}
	if (first == 0 || second == 0) {
		return first - second;
	}

	const unsigned char *a = (const unsigned char*)(first);
	const unsigned char *b = (const unsigned char*)(second);
	Size index = 0;
	for (; index < length && *a && *b; ++a, ++b, ++index) {
		if (*a != *b) {
			return *a - *b;
		}
	}

	if (index == length) {
		return 0;
	} else {
		return *a - *b;
	}
}

Size Utils::strlen(const char* string) {
	const char* needle = string;
	for (; *needle; ++needle) {
	}
	return needle - string;
}

const char* Utils::basename(const char* path) {
	if (path == 0) {
		return 0;
	}

	static char storage[512];
	const char* needle = path + strlen(path);
	--needle;
	bool directory = false;
	if (*needle == '/') {
		directory = true;
		--needle;
	}
	for (;needle >= path && *needle != '/'; --needle) {
	}
	Size length = strncpy(storage, needle + 1, sizeof(storage));
	if (directory) {
		storage[length - 1] = 0;
	}
	return storage;
}

Size Utils::ceilingDivide(Size value, Size round) {
	if (value % round == 0) {
		return value / round;
	} else {
		return value / round + 1;
	}
}

Size Utils::roundUp(Size size, Size round) {
	if (size % round == 0) {
		return size;
	} else {
		return (size / round + 1) * round;
	}
}

Size Utils::roundDown(Size size, Size round) {
	return size / round * round;
}

} // namespace kernel
