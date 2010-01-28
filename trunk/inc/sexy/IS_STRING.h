#ifndef KERNEL_SEXY_IS_STRING_H_INCLUDED
#define KERNEL_SEXY_IS_STRING_H_INCLUDED

template<typename Type>
class IS_STRING {
public:
	enum {
		value = 0
	};
};

template<>
class IS_STRING<char*> {
public:
	enum {
		value = 1
	};
};

template<>
class IS_STRING<const char*> {
public:
	enum {
		value = 1
	};
};

template<int SIZE>
class IS_STRING<char[SIZE]> {
public:
	enum {
		value = 1
	};
};

template<int SIZE>
class IS_STRING<const char[SIZE]> {
public:
	enum {
		value = 1
	};
};

#endif
