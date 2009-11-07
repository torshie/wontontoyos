#ifndef __WONTON_SEXY_TERNARY_H_INCLUDED__
#define __WONTON_SEXY_TERNARY_H_INCLUDED__

namespace sexy {

template<bool b, typename First, typename Second> class TERNARY;

template<typename First, typename Second>
class TERNARY<true, First, Second> {
public:
	typedef First T;
};

template<typename First, typename Second>
class TERNARY<false, First, Second> {
public:
	typedef Second T;
};

}

#endif
