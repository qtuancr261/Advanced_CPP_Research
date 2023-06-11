#include "message.h"

Message::Message()
	: _id{0} {
}

Message::Message(int initId)
	: _id{initId} {
}

Message::Message(const Message &other)
	: _id{other.getId()} {
}

Message::~Message() {
}

int Message::getId() const {
	return _id;
}
