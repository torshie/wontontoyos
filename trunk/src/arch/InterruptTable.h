#ifndef KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED
#define KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED

#include <generic/type.h>
#include "arch/getProcessorInstance.h"
#include <generic/STATIC_ASSERT.h>

namespace kernel {

class InterruptTable {
	friend InterruptTable& getProcessorInstance<InterruptTable>();
public:
	enum {
		HANDLER_DOUBLE_FAULT = 8,
		HANDLER_PAGE_FAULT = 14,

		HANDLER_HPET_TIMER = 33,

		HANDLER_IRQ8 = 0x70,

		/**
		 * !!!!!!!!!!!!!!!!
		 * !!! Warning !!!!
		 * !!!!!!!!!!!!!!!!
		 * If you want to change this const, make sure you have changed file
		 * interruptServiceRoutine.S
		 */
		HANDLER_COUNT = 128
	};

	void setHandler(int isrNumber, void (*handler)(void));

private:
	class Descriptor {
		friend class InterruptTable;
		Descriptor();

		void setOffset(Address offset) {
			offset0 = offset;
			offset1 = offset >> 16;
			offset2 = offset >> 32;
		}

	public:
		U16 offset0;
		U16 selector;
	private:
		U8 ist:3;
		U8 ignored0:5;
	public:
		U8 type:4;
		U8 zero0:1;
		U8 dpl:2;
		U8 present:1;
		U16 offset1;
		U32 offset2;
	private:
		U32 ignored1;
	} __attribute__((packed));

	void (*handler[HANDLER_COUNT])(void);

	Descriptor table[HANDLER_COUNT];
	char __padding[sizeof(U64) - sizeof(U16)];
	U16 limit;
	U64 address;

	InterruptTable();
	void load() const;

	~InterruptTable() {}
	InterruptTable(const InterruptTable&);
	const InterruptTable& operator=(const InterruptTable&);

	// Yes, handle is private. Assembly is used to get access to this static method
	static void handle(unsigned int isrNumber);
} __attribute__((packed));

inline void InterruptTable::setHandler(int isrNumber, void (*h)(void)) {
	handler[isrNumber] = h;
}

inline void InterruptTable::load() const {
	asm volatile("lidt %0\n"
			"sti" : : "m"(limit));
}

} // namespace kernel

#endif // KERNEL_ARCH_INTERRUPT_DESCRIPTOR_TABLE_H_INCLUDED
