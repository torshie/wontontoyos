#ifndef KERNEL_SEXY_TYPE_SELECTOR_H_INCLUDED
#define KERNEL_SEXY_TYPE_SELECTOR_H_INCLUDED

#include <sexy/STATIC_ASSERT.h>

namespace kernel {

// XXX Remove duplication with macro
template<
bool B1 = false, typename T1 = void,
bool B2 = false, typename T2 = void,
bool B3 = false, typename T3 = void,
bool B4 = false, typename T4 = void,
bool B5 = false, typename T5 = void,
bool B6 = false, typename T6 = void,
bool B7 = false, typename T7 = void,
bool B8 = false, typename T8 = void,
bool B9 = false, typename T9 = void
> class TYPE_SELECTOR;

template<
typename T1,
bool B2, typename T2,
bool B3, typename T3,
bool B4, typename T4,
bool B5, typename T5,
bool B6, typename T6,
bool B7, typename T7,
bool B8, typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
true, T1,
B2, T2,
B3, T3,
B4, T4,
B5, T5,
B6, T6,
B7, T7,
B8, T8,
B9, T9
> {
public:
	typedef T1 Type;
};

template<
typename T1,
typename T2,
bool B3, typename T3,
bool B4, typename T4,
bool B5, typename T5,
bool B6, typename T6,
bool B7, typename T7,
bool B8, typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
false, T1,
true, T2,
B3, T3,
B4, T4,
B5, T5,
B6, T6,
B7, T7,
B8, T8,
B9, T9
> {
public:
	typedef T2 Type;
};

template<
typename T1,
typename T2,
typename T3,
bool B4, typename T4,
bool B5, typename T5,
bool B6, typename T6,
bool B7, typename T7,
bool B8, typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
false, T1,
false, T2,
true, T3,
B4, T4,
B5, T5,
B6, T6,
B7, T7,
B8, T8,
B9, T9
> {
public:
	typedef T3 Type;
};

template<
typename T1,
typename T2,
typename T3,
typename T4,
bool B5, typename T5,
bool B6, typename T6,
bool B7, typename T7,
bool B8, typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
false, T1,
false, T2,
false, T3,
true, T4,
B5, T5,
B6, T6,
B7, T7,
B8, T8,
B9, T9
> {
public:
	typedef T4 Type;
};

template<
typename T1,
typename T2,
typename T3,
typename T4,
typename T5,
bool B6, typename T6,
bool B7, typename T7,
bool B8, typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
false, T1,
false, T2,
false, T3,
false, T4,
true, T5,
B6, T6,
B7, T7,
B8, T8,
B9, T9
> {
public:
	typedef T5 Type;
};

template<
typename T1,
typename T2,
typename T3,
typename T4,
typename T5,
typename T6,
bool B7, typename T7,
bool B8, typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
false, T1,
false, T2,
false, T3,
false, T4,
false, T5,
true, T6,
B7, T7,
B8, T8,
B9, T9
> {
public:
	typedef T6 Type;
};

template<
typename T1,
typename T2,
typename T3,
typename T4,
typename T5,
typename T6,
typename T7,
bool B8, typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
false, T1,
false, T2,
false, T3,
false, T4,
false, T5,
false, T6,
true, T7,
B8, T8,
B9, T9
> {
public:
	typedef T7 Type;
};

template<
typename T1,
typename T2,
typename T3,
typename T4,
typename T5,
typename T6,
typename T7,
typename T8,
bool B9, typename T9
> class TYPE_SELECTOR<
false, T1,
false, T2,
false, T3,
false, T4,
false, T5,
false, T6,
false, T7,
true, T8,
B9, T9
> {
public:
	typedef T8 Type;
};

template<
typename T1,
typename T2,
typename T3,
typename T4,
typename T5,
typename T6,
typename T7,
typename T8,
typename T9
> class TYPE_SELECTOR<
false, T1,
false, T2,
false, T3,
false, T4,
false, T5,
false, T6,
false, T7,
false, T8,
true, T9
> {
public:
	typedef T9 Type;
};

STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<1, char[1]>::Type), 1);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 1, char[2]>::Type), 2);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 0, char[2], 1, char[3]>::Type), 3);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 0, char[2], 0, char[3],
		1, char[4]>::Type), 4);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 0, char[2], 0, char[3],
		0, char[4], 1, char[5]>::Type), 5);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 0, char[2], 0, char[3],
		0, char[4], 0, char[5], 1, char[6]>::Type), 6);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 0, char[2], 0, char[3],
		0, char[4], 0, char[5], 0, char[6], 1, char[7]>::Type), 7);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 0, char[2], 0, char[3],
		0, char[4], 0, char[5], 0, char[6], 0, char[7], 1, char[8]>::Type), 8);
STATIC_ASSERT_EQUAL(sizeof(TYPE_SELECTOR<0, char[1], 0, char[2], 0, char[3],
		0, char[4], 0, char[5], 0, char[6], 0, char[7], 0, char[8], 1, char[9]>::Type), 9);

} // namespace kernel

#endif // KERNEL_SEXY_TYPE_SELECTOR_H_INCLUDED
