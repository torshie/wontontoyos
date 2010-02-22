#ifndef KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>
#include <generic/STATIC_ASSERT.h>

namespace kernel {

class InterruptDescriptorTable {
	friend InterruptDescriptorTable& getSingleInstance<InterruptDescriptorTable>();
public:
	enum {
		DOUBLE_FAULT = 8,
		PAGE_FAULT = 14,

		/**
		 * !!!!!!!!!!!!!!!!
		 * !!! Warning !!!!
		 * !!!!!!!!!!!!!!!!
		 * If you want to change this const, make sure you have changed file
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

	void (*handler[HANDLER_COUNT])(void);

	InterruptDescriptor table[HANDLER_COUNT];
	char __padding[sizeof(U64) - sizeof(U16)];
	U16 limit;
	U64 address;

	InterruptDescriptorTable();
	~InterruptDescriptorTable() {}
	InterruptDescriptorTable(const InterruptDescriptorTable&);
	const InterruptDescriptorTable& operator=(const InterruptDescriptorTable&);

	// Yes, handle is private. We will use assembly to get access to it
	static void handle(int isrNumber);
} __attribute__((packed));

inline void InterruptDescriptorTable::setHandler(int isrNumber, void (*h)(void)) {
	handler[isrNumber] = h;
}

inline void InterruptDescriptorTable::load() const {
	asm volatile("lidt %0; sti" : : "m"(limit));
}

} /* namespace kernel */

#endif /* KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED */
