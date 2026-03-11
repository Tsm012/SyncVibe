#include "Message.h"

Network::Message::Message()
{
}

Network::Message::Message(MessageType type, std::vector<unsigned char> serializedMessage) : messageType(type), payload(serializedMessage)
{
}

Network::Message::Message(enet_uint8* data, size_t size)
{
	std::vector<unsigned char> receivedData(data, data + size);
	messageType = static_cast<MessageType>(receivedData[0]);
	payload.insert(payload.end(), receivedData.begin() + 1, receivedData.end());
}

Network::Message::~Message()
{
}