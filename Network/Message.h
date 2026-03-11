#pragma once
#include <vector>
#include <enet/types.h>

namespace Network
{
	class Message
	{
	public:

		enum MessageType
		{
			Hello,
			Replication
		};

		Message();
		Message(MessageType type, std::vector<unsigned char> serializedMessage);
		Message(enet_uint8* data, size_t size);
		~Message();

		std::vector<unsigned char> serializeMessage() const
		{
			std::vector<unsigned char> serializedMessage;
			serializedMessage.push_back(static_cast<unsigned char>(messageType));
			serializedMessage.insert(serializedMessage.end(), payload.begin(), payload.end());
			return serializedMessage;
		}
		MessageType getMessageType() const
		{
			return messageType;
		}
		const std::vector<unsigned char>& getPayload() const
		{
			return payload;
		}
	private:
		MessageType messageType;
		std::vector<unsigned char> payload;

	};
}
