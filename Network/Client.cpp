#include "Client.h"
#include <random>
#include <thread>
#include <string>
#include <Utilities.h>
#include <string.h>


namespace Network
{
	Client::Client(const char* hostAddress, int port)
	{
		if (enet_initialize() != 0)
		{
			std::cerr << "An error occurred while initializing ENet." << std::endl;
		}

		host = enet_host_create(nullptr, 1, 2, 0, 0);
		if (host == nullptr)
		{
			std::cerr << "An error occurred while trying to create an ENet client host."
				<< std::endl;
		}

		ENetAddress address;
		enet_address_set_host(&address, hostAddress);
		address.port = port;
		peer = enet_host_connect(host, &address, 2, 0);

		if (peer == nullptr)
		{
			std::cerr << "No available peers for initiating an ENet connection."
				<< std::endl;
			enet_host_destroy(host);
		}
		connected = true;
	}

	Client::~Client()
	{
		if (host != nullptr)
		{
			enet_host_destroy(host);
		}
		enet_deinitialize();
	}

	void Client::start()
	{
		while (connected)
		{
			auto messages = channel.fetchSendData();

			for (auto& message : messages)
			{
				sendData(peer, message.second);
				channel.removeSendData(message.first);
			}
		}
	}

	unsigned int Network::Client::initialize()
	{
		std::vector<unsigned char> serializedPlayerId;
		serializedPlayerId.push_back(generateRandomId());
		auto helloMessage = Network::Message(Network::Message::Hello, serializedPlayerId);
		channel.addMessageChannel(0);
		unsigned int playerId = 0;
		while (playerId == 0)
		{
			channel.setDataToSend(helloMessage);
			std::this_thread::sleep_for(std::chrono::seconds(1));
			auto channels = channel.fetchReceivedData();

			for (auto& channel : channels)
			{
				for (auto& message : channel.second)
				{
					if (message.second.getMessageType() == Network::Message::Hello)
					{
						memcpy(&playerId, message.second.getPayload().data(), sizeof(unsigned int));
						std::cout << "Player ID: " << playerId << std::endl;
						return playerId;
					}
				}
			}
		}
		return -1;
	}
}
