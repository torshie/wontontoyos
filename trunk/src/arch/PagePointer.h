#ifndef KERNEL_ARCH_PAGE_POINTER_H_INCLUDED
#define KERNEL_ARCH_PAGE_POINTER_H_INCLUDED

#include <generic/type.h>

namespace kernel {

class BasePointer {
protected:
	BasePointer() : initializer(0) {}
	BasePointer(const BasePointer&);
	const BasePointer& operator = (const BasePointer&);

public:
	enum {
		PRESENT = 1 << 0,
		WRITABLE = 1 << 1,
		USERSPACE = 1 << 2,
		WRITE_THROUGH = 1 << 3,
		CACHE_DISABLE = 1 << 4,
		ACCESSED = 1 << 5,
		DIRTY = 1 << 6,
		GLOBAL = 1 << 8,
		NO_EXECUTE = (U64)1 << 63
	};
	union {
		U64 initializer;
	public:
		struct {
			U8 present:1;
			U8 writable:1;
			U8 userspace:1;
			U8 writeThrough:1;
			U8 cacheDisable:1;
			U8 accessed:1;
			U8 dirty:1;
			U8 __pat:1;
			U8 global:1;
			U8 __reserved_1:3;
			U64 page:40;
			U16 __reserved_2:11;
			U8 noExecute:1;
		} __attribute__((packed));

		U64 physicalAddress;
	};
} __attribute__((packed));

template<int LEVEL>
class PagePointer;

#ifdef HIDE_PARENT_MEMBER
#error "HIDE_PARENT_MEMBER is already defined"
#else
#define HIDE_PARENT_MEMBER(member) \
	private: using BasePointer::member
#endif

template<>
class PagePointer<4> : public BasePointer {
	HIDE_PARENT_MEMBER(DIRTY);
	HIDE_PARENT_MEMBER(GLOBAL);
	HIDE_PARENT_MEMBER(dirty);
	HIDE_PARENT_MEMBER(global);
	HIDE_PARENT_MEMBER(__pat);
	HIDE_PARENT_MEMBER(__reserved_1);
	HIDE_PARENT_MEMBER(__reserved_2);
} __attribute__((packed));

template<>
class PagePointer<3> : public BasePointer {
	HIDE_PARENT_MEMBER(DIRTY);
	HIDE_PARENT_MEMBER(GLOBAL);
	HIDE_PARENT_MEMBER(dirty);
	HIDE_PARENT_MEMBER(global);
	HIDE_PARENT_MEMBER(__pat);
	HIDE_PARENT_MEMBER(__reserved_1);
	HIDE_PARENT_MEMBER(__reserved_2);
} __attribute__((packed));

template<>
class PagePointer<2> : public BasePointer {
	HIDE_PARENT_MEMBER(DIRTY);
	HIDE_PARENT_MEMBER(GLOBAL);
	HIDE_PARENT_MEMBER(dirty);
	HIDE_PARENT_MEMBER(global);
	HIDE_PARENT_MEMBER(__pat);
	HIDE_PARENT_MEMBER(__reserved_1);
	HIDE_PARENT_MEMBER(__reserved_2);
} __attribute__((packed));

template<>
class PagePointer<1> : public BasePointer {
	HIDE_PARENT_MEMBER(__pat);
	HIDE_PARENT_MEMBER(__reserved_1);
	HIDE_PARENT_MEMBER(__reserved_2);
} __attribute__((packed));

#undef HIDE_PARENT_MEMBER

namespace internal {

/**
 * Used to make sure the data structure is correctly packed.
 *
 * If the data structure isn't packed as expected, we will get compile
 * time error.
 */
typedef int StaticSizeChecker[sizeof(PagePointer<1>) == 8 ? 1 : -1];
typedef int StaticSizeChecker[sizeof(PagePointer<2>) == 8 ? 1 : -1];
typedef int StaticSizeChecker[sizeof(PagePointer<3>) == 8 ? 1 : -1];
typedef int StaticSizeChecker[sizeof(PagePointer<4>) == 8 ? 1 : -1];

} /* namespace internal */

} /* namespace kernel */

#endif /* KERNEL_ARCH_PAGE_POINTER_H_INCLUDED */
