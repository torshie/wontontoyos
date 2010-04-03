#ifndef KERNEL_SEXY_IS_CLASS_H_INCLUDED
#define KERNEL_SEXY_IS_CLASS_H_INCLUDED

namespace kernel {

template<typename T> class IS_CLASS {
	typedef char One;
	typedef struct { char member[2]; } Two;

	template<typename C> static One check(void (C::*)(void));
	template<typename C> static Two check(...);
public:
	enum {
		value = (sizeof(IS_CLASS::check<T>(0)) == 1 ? 1 : 0)
	};
};

} // namespace kernel

#endif // KERNEL_SEXY_IS_CLASS_H_INCLUDED
