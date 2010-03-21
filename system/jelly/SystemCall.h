#ifndef JELLY_SYSTEM_CALL_H_INCLUDED
#define JELLY_SYSTEM_CALL_H_INCLUDED

#include <kernel/abi.h>

namespace jelly {

template<int CALL> class SystemCall;

template<> class SystemCall<kernel::SYSCALL_EXIT_PROCESS> {
public:
	static void call(int status);
};

template<> class SystemCall<kernel::SYSCALL_RETURN_VALUE> {
public:
	static int call();
};

template<> class SystemCall<kernel::SYSCALL_DOUBLE_INPUT> {
public:
	static int call(int input);
};

template<> class SystemCall<kernel::SYSCALL_SUM> {
public:
	static int call(int a, int b, int c, int d);
};

} // namespace jelly

#endif // JELLY_SYSTEM_CALL_H_INCLUDED
