#include "Message.h"

namespace kernel {

Message Message::debug(Message::DEBUG);
Message Message::verbose(Message::VERBOSE);
Message Message::info(Message::INFO);
Message Message::brief(Message::BRIEF);
Message Message::warning(Message::WARNING);
Message Message::error(Message::ERROR);
Message Message::critical(Message::CRITICAL);
Message Message::fatal(Message::FATAL);

} // namespace kernel
