#ifndef __WONTON_KERNEL_INTERRUPT_DESCRIPTOR_TABLE_H__
#define __WONTON_KERNEL_INTERRUPT_DESCRIPTOR_TABLE_H__

#include <base/type.h>
#include <base/getSingleInstance.h>

namespace kernel {

class InterruptDescriptorTable {
	friend InterruptDescriptorTable&
			base::getSingleInstance<InterruptDescriptorTable>();
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
		base::U16 offset0;
		base::U16 selector;
		base::U8 ist:3;
		base::U8 ignored0:5;
		base::U8 type:4;
		base::U8 zero0:1;
		base::U8 dpl:2;
		base::U8 present:1;
		base::U16 offset1;
		base::U32 offset2;
		base::U32 ignored1;

		/**
		 * XXX As InterruptDescriptor must have a default constructor, we need
		 * to make the interface of InterruptDescriptor to be this. Although
		 * C++0x support initialize array members, C++0x are always
		 * unavailable.
		 */
		InterruptDescriptor();

		void setOffset(base::Address offset) {
			offset0 = offset;
			offset1 = offset >> 16;
			offset2 = offset >> 32;
		}
	} __attribute__((packed));

	/**
	 * As this structure is packed, we should put the handlers before member
	 * limit, otherwise we will suffer from performance overhead.
	 *
	 * XXX Remove the static modifier
	 */
	void (*handler[HANDLER_COUNT])(void);

	InterruptDescriptor table[HANDLER_COUNT];
	base::U16 limit;
	base::U64 address;

	InterruptDescriptorTable();
	~InterruptDescriptorTable() {}
	InterruptDescriptorTable(const InterruptDescriptorTable&);
	const InterruptDescriptorTable& operator=(const InterruptDescriptorTable&);

	/**
	 * Yes, handle is private. We will use assembly to get access to it
	 */
	static void handle(int isrNumber);

	/**
	 * Make sure that InterruptDescriptor is correctly packed. Since
	 * InterruptDescriptor is private, we cannot put this declaration into
	 * namespace insurance
	 */
	void insure(char [sizeof(InterruptDescriptor) == 16 ? 1 : -1]);
} __attribute__((packed));

inline void InterruptDescriptorTable::setHandler(int isrNumber,
		void (*h)(void)) {
	handler[isrNumber] = h;
}

inline void InterruptDescriptorTable::load() const {
	asm volatile("lidt %0; sti" : : "m"(limit));
}

} /* namespace kernel */

#endif
