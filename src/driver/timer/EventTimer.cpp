#include "EventTimer.h"
#include "arch/X64Constant.h"
#include "arch/InputOutputController.h"
#include "arch/InterruptTable.h"
#include "Message.h"

namespace kernel {

EventTimer::EventTimer() {
	InputOutputController::Router router(InterruptTable::HANDLER_HPET_TIMER);
	InputOutputController& controller = getSingleInstance<InputOutputController>();
	controller.setRouter(InputOutputController::ROUTER_ENTRY_HPET, router);
	Message::brief << "Timer Count: " << id.timerCount << "\n";
	Message::brief << "Timer Block Address: " << this << "\n";
}

} // namespace kernel
