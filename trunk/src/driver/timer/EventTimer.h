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

namespace kernel {

class EventTimer {
	friend EventTimer& getSingleInstance<EventTimer>(Address);

	EventTimer();
	EventTimer(const EventTimer&);
	const EventTimer& operator = (const EventTimer&);

	struct {
		U8 version;
		U8 timerCount:5;
		U8 wideTimer:1;
		U8 __reserved:1;
		U8 legacy:1;
		U16 vendorId;
		U32 period;
	} __attribute__((packed)) id;

	U64 __reserved0;

	struct Config {
		U8 legacy:1;
		U64 __reserved:63;
		Config() : legacy(0), __reserved(0) {}
	} __attribute__((packed)) config;

	U64 __reserved1;
	U64 status;
	U64 __reserved2[25];
	U64 mainCounter;
	U64 __reserved3;

	struct {
		struct Config {
			U8 __reserved1:1;
			U8 levelTriggered:1;
			U8 enabled:1;
			U8 __unused1:1;
			U8 periodicCapable:1;
			U8 wideTimer:1;
			U8 enablePeriodic:1;
			U8 __reserved2:1;
			U8 narrowMode:1;
			volatile U8 interrupt:5;
			U8 __unused2:2;
			U16 __reserved3;
			U32 possibleInterrupt;
		} __attribute__((packed)) config;
		U32 comparator;
		U32 __reserved;
		U64 __unused[2];
	} __attribute__((packed)) timer[32];

} __attribute__((packed));

template<> inline EventTimer& getSingleInstance<EventTimer>(Address physical) {
	static bool initialized = false;
	if (initialized) {
		return *(EventTimer*)VIRTUAL_BASE_HPET;
	}

	PageMap::create(VIRTUAL_BASE_HPET, MEMORY_SIZE_HPET, physical - PAGE_SIZE);
	EventTimer* timer = new ((void*)VIRTUAL_BASE_HPET)EventTimer();
	initialized = true;
	return *timer;
}

} // namespace kernel

#endif // KERNEL_DRIVER_TIMER_EVENT_TIMER_H_INCLUDED
