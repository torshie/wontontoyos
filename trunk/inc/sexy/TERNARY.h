#ifndef KERNEL_SEXY_TERNARY_H_INCLUDED
#define KERNEL_SEXY_TERNARY_H_INCLUDED

namespace kernel {

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

#endif /* KERNEL_SEXY_TERNARY_H_INCLUDED */
