#pragma once
#include "ThreadSafeByteChannel.h"
#include "NetworkConnection.h"
#include <iostream>

namespace Network
{
	class Client : public NetworkConnection
	{
	public:
		Client(const char* hostAddress, int port);
		~Client();

		void start() override;
		unsigned int initialize() override;
	private:
		ENetPeer* peer;
	};
}
