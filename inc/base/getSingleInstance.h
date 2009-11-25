#ifndef __WONTON_BASE_GET_SINGLE_INSTANCE_H_INCLUDED__
#define __WONTON_BASE_GET_SINGLE_INSTANCE_H_INCLUDED__

namespace base {

/**
 * XXX Make this function thread-safe, although it is when compiled
 * with g++
 */
template<typename T>
T& getSingleInstance() {
	static T instance;
	return instance;
}

}

#endif
