#include "Message.h"
#include "MessageLevel.h"

namespace kernel {

Message Message::debug(MessageLevel::DEBUG);
Message Message::verbose(MessageLevel::VERBOSE);
Message Message::info(MessageLevel::INFO);
Message Message::brief(MessageLevel::BRIEF);
Message Message::warning(MessageLevel::WARNING);
Message Message::error(MessageLevel::ERROR);
Message Message::critical(MessageLevel::CRITICAL);
Message Message::fatal(MessageLevel::FATAL);

} // namespace kernel
