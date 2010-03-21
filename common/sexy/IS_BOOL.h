#ifndef KERNEL_SEXY_IS_BOOL_H_INCLUDED
#define KERNEL_SEXY_IS_BOOL_H_INCLUDED

namespace kernel {

template<typename T> class IS_BOOL {
public:
	enum {
		value = 0
	};
};

template<> class IS_BOOL<bool> {
public:
	enum {
		value = 1
	};
};

} // namespace kernel

#endif // KERNEL_SEXY_IS_BOOL_H_INCLUDED
