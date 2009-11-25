#ifndef __WONTON_SEXY_IS_CHAR_POINTER_H__
#define __WONTON_SEXY_IS_CHAR_POINTER_H__

template<typename T>
class IS_CHAR_POINTER {
public:
	enum {
		value = 0
	};
};

template<>
class IS_CHAR_POINTER<char*> {
public:
	enum {
		value = 1
	};
};

#endif
