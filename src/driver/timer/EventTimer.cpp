#include "EventTimer.h"
#include "arch/X64Constant.h"
#include "arch/InputOutputController.h"
#include "arch/InterruptTable.h"
#include "Message.h"
#include "arch/Processor.h"

namespace kernel {

template<> EventTimer& getSingleInstance<EventTimer>() {
	static bool initialized = false;
	EventTimer* timer = (EventTimer*)VIRTUAL_BASE_HPET;
	if (initialized) {
		return *timer;
	}
	Address physical = Property::get<Property::PARAM_EVENT_TIMER_BASE, Address>();
	PageMap::create(VIRTUAL_BASE_HPET, MEMORY_SIZE_HPET, physical);
	return *(new (timer)EventTimer());
}

EventTimer::EventTimer() {
	int periodicTimer = getPeriodicTimer();
	if (periodicTimer < 0) {
		Message::brief << "Cannot find periodic timer " << "\n";
		Processor::halt();
	} else {
		Message::brief << "Got periodic timer: " << periodicTimer << "\n";
	}

	int interrupt = getAvailableInterrupt(periodicTimer);
	TimerConfig timerConfig;
	timerConfig.__value = timer[periodicTimer].config.__value;
	timerConfig.interrupt = interrupt;
	timerConfig.periodic = 1;
	timerConfig.levelTrigger = 0;
	timerConfig.setValue = 1;
	timerConfig.enable = 1;
	timer[periodicTimer].config.__value = timerConfig.__value;
	timer[periodicTimer].comparator = 0x20000000;

	InputOutputController::Router router(InterruptTable::HANDLER_HPET_TIMER);
	InputOutputController& controller = getSingleInstance<InputOutputController>();
	controller.setRouter(interrupt, router);

	GeneralConfig generalConfig;
	generalConfig.__value = config.__value;
	generalConfig.enable = 1;
	generalConfig.legacy = 0;
	config.__value = generalConfig.__value;
}

int EventTimer::getAvailableInterrupt(int timerIndex) const {
	int interrupt = 0;
	for (; (timer[timerIndex].config.possibleInterrupt & (1 << interrupt)) == 0; ++interrupt)
		;
	return interrupt;
}

int EventTimer::getPeriodicTimer() const {
	GeneralId buffer;
	buffer.__value = id.__value;
	for (unsigned int i = 0; i < buffer.timerCount; ++i) {
		TimerConfig tc;
		tc.__value = timer[i].config.__value;
		if (tc.periodicCapable) {
			return i;
		}
	}
	return -1;
}

} // namespace kernel
