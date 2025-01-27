#include "Server.h"
#include <iostream>
#include <stdexcept> 

namespace Network
{
	Server::Server()
	{
		if (enet_initialize() != 0)
		{
			throw std::runtime_error("An error occurred while initializing ENet.");
		}

		initialize();

		ENetAddress address{};
		address.host = ENET_HOST_ANY;
		address.port = port;
		host = enet_host_create(&address, 20, 2, 0, 0);

		if (host == nullptr)
		{
			throw std::runtime_error("An error occurred while trying to create an ENet client host.");
		}
		connected = true;
	}

	Server::~Server()
	{
		if (host != nullptr)
		{
			enet_host_destroy(host);
		}
		enet_deinitialize();
	}

	void Server::start()
	{
		while (connected)
		{
			auto messages = channel.fetchSendData();

			for (auto& peer : channel.peers)
			{
				for (auto& message : messages)
				{
					sendData(peer, message.second);
					channel.removeSendData(message.first);
				}
			}
		}
	}

	unsigned int Server::initialize()
	{
		ENetAddress address{};
		address.host = ENET_HOST_ANY;
		for (port = 2000; port <= 4000; port++)
		{
			address.port = port;
			ENetHost* server = enet_host_create(&address, 2, 2, 0, 0);
			if (server)
			{
				enet_host_destroy(server);
				std::cout << "Server port selected: " << port << std::endl;
				return 0;
			}
		}
		throw std::runtime_error("Unable to find open port between 2000 - 4000");
	}
}
