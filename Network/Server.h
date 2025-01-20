#pragma once
#include <enet.h>
#include "NetworkConnection.h"


namespace Network
{
	class Server : public NetworkConnection
	{
	public:
		Server();
		~Server();
		void start() override;
		unsigned int initialize() override;

	private:
		uint16_t port = 2000;
	};
}
