#ifndef KERNEL_SEXY_TYPE_SELECTOR_H_INCLUDED
#define KERNEL_SEXY_TYPE_SELECTOR_H_INCLUDED

namespace kernel {

template<bool b, typename First, typename Second> class TYPE_SELECTOR;

template<typename First, typename Second> class TYPE_SELECTOR<true, First, Second> {
public:
	typedef First Type;
};

template<typename First, typename Second> class TYPE_SELECTOR<false, First, Second> {
public:
	typedef Second Type;
};

} // namespace kernel

#endif // KERNEL_SEXY_TYPE_SELECTOR_H_INCLUDED
