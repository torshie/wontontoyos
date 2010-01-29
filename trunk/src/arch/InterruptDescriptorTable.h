#ifndef KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>

namespace kernel {

class InterruptDescriptorTable {
	friend InterruptDescriptorTable&
			getSingleInstance<InterruptDescriptorTable>();
public:
	enum {
		PAGE_FAULT = 14,

		/**
		 * If you want to change this const, please also change file
		 * interruptServiceRoutine.S
		 */
		HANDLER_COUNT = 32
	};

	void load() const;
	void setHandler(int isrNumber, void (*handler)(void));

private:
	struct InterruptDescriptor {
		U16 offset0;
		U16 selector;
		U8 ist:3;
		U8 ignored0:5;
		U8 type:4;
		U8 zero0:1;
		U8 dpl:2;
		U8 present:1;
		U16 offset1;
		U32 offset2;
		U32 ignored1;

		/**
		 * XXX Event InterruptDescriptor must have a default constructor, we
		 * still have to make the interface of InterruptDescriptor to be like
		 * this. Although C++0x support initialize array members, C++0x are
		 * always unavailable.
		 */
		InterruptDescriptor();

		void setOffset(Address offset) {
			offset0 = offset;
			offset1 = offset >> 16;
			offset2 = offset >> 32;
		}
	} __attribute__((packed));

	/**
	 * As this structure is packed, we should put the handlers before member
	 * limit, otherwise we will suffer from performance overhead.
	 */
	void (*handler[HANDLER_COUNT])(void);

	InterruptDescriptor table[HANDLER_COUNT];
	U16 limit;
	U64 address;

	InterruptDescriptorTable();
	~InterruptDescriptorTable() {}
	InterruptDescriptorTable(const InterruptDescriptorTable&);
	const InterruptDescriptorTable& operator=(const InterruptDescriptorTable&);

	/**
	 * Yes, handle is private. We will use assembly to get access to it
	 */
	static void handle(int isrNumber);

	/**
	 * Used to make sure the data structure is correctly packed.
	 *
	 * If the data structure isn't packed as expected, we will get compile
	 * time error.
	 */
	typedef char StaticSizeChecker[sizeof(InterruptDescriptor) == 16 ? 1 : -1];
} __attribute__((packed));

inline void InterruptDescriptorTable::setHandler(int isrNumber,
		void (*h)(void)) {
	handler[isrNumber] = h;
}

inline void InterruptDescriptorTable::load() const {
	asm volatile("lidt %0; sti" : : "m"(limit));
}

} /* namespace kernel */

#endif /* KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED */
