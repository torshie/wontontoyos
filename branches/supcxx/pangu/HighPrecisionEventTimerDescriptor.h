#ifndef PANGU_HIGH_PRECISION_EVENT_TIMER_DESCRIPTOR_H_INCLUDED
#define PANGU_HIGH_PRECISION_EVENT_TIMER_DESCRIPTOR_H_INCLUDED

#include <generic/type.h>

namespace pangu {

struct HighPrecisionEventTimerDescriptor {
	kernel::U32 blockId;
	kernel::U8 addressSpace;
	kernel::U8 bitWidth;
	kernel::U8 bitOffset;
	kernel::U8 __reserved;
	kernel::U64 address;
	kernel::U8 number;
	kernel::U16 minTick;
	kernel::U8 attribute;
} __attribute__((packed));

} // namespace pangu

#endif // PANGU_HIGH_PRECISION_EVENT_TIMER_DESCRIPTOR_H_INCLUDED
