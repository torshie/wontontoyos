#ifndef KERNEL_DRIVER_TIMER_EVENT_TIMER_H_INCLUDED
#define KERNEL_DRIVER_TIMER_EVENT_TIMER_H_INCLUDED

#include <generic/type.h>
#include <generic/getSingleInstance.h>
#include "arch/InterruptController.h"
#include <cxx/new.h>
#include <kernel/abi.h>
#include "arch/X64Constant.h"
#include "mm/PageMap.h"
#include <generic/STATIC_ASSERT.h>
#include "Message.h"

namespace kernel {

class EventTimer {
	friend EventTimer& getSingleInstance<EventTimer>();

	EventTimer();
	EventTimer(const EventTimer&);
	const EventTimer& operator = (const EventTimer&);

	struct GeneralId {
		union {
			struct {
				U8 version;
				U8 timerCount :5;
				U8 wideTimer :1;
				U8 __reserved :1;
				U8 legacy :1;
				U16 vendorId;
			} __attribute__((packed));
			U32 __value;
		};
		U32 period;
	} __attribute__((packed));

	union GeneralConfig {
		struct {
			U8 enable :1;
			U8 legacy :1;
			U64 __reserved :62;
		};
		U64 __value;
	} __attribute__((packed));

	struct TimerConfig {
		union {
			struct {
				U8 __reserved1 :1;
				U8 levelTrigger :1;
				U8 enable :1;
				U8 periodic :1;
				U8 periodicCapable :1;
				U8 wideTimer :1;
				U8 setValue :1;
				U8 __reserved2 :1;
				U8 narrowMode :1;
				U8 interrupt :5;
				U8 __unused1 :2;
				U16 __reserved3;
			}__attribute__((packed));
			U32 __value;
		};
		U32 possibleInterrupt;
	} __attribute__((packed));

	/**
	 * HPET registers only accept 32-bit or 64-bit access, so in order by read/write HPET
	 * registers, temporary buffers should be created. The keyword volatile is used to prevent
	 * the compiler from optimizing out the creation of temporary buffers.
	 */
	volatile GeneralId id;
	U64 __reserved0;
	GeneralConfig config;

	U64 __reserved1;
	U64 status;
	U64 __reserved2[25];
	volatile U64 mainCounter;
	U64 __reserved3;

	struct {
		volatile TimerConfig config;
		volatile U64 comparator;
		U64 __unused[2];
	} __attribute__((packed)) timer[24];

	int getAvailableInterrupt(int timerIndex) const;
	int getPeriodicTimer() const;

} __attribute__((packed));

STATIC_ASSERT_EQUAL(sizeof(EventTimer), 1024);

template<> EventTimer& getSingleInstance<EventTimer>();

} // namespace kernel

#endif // KERNEL_DRIVER_TIMER_EVENT_TIMER_H_INCLUDED
