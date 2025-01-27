// Engine.cpp : Defines the functions for the static library.
#include "Engine.h"
#include <map>
#include <thread>
#include <cstring>

Engine::Engine() : connectionType(Server), host("localhost"), port(2000)
{
	initialize(connectionType, host, port);
	auto texture = ui.loadTexture("Player.bmp");
	playerId = generateRandomId();
	players.insert({ playerId, Sprite(playerId, texture, SDL_FRect{250, 100, 175, 100}, 15) });
}

Engine::Engine(ConnectionType connectionType, const char* host, int port)
	: connectionType(connectionType), host(host), port(port)
{
	initialize(connectionType, host, port);
}

void Engine::initialize(Engine::ConnectionType connectionType, const char* host, int port)
{
	switch (connectionType)
	{
	case Engine::Server:
	{
		connection = new Network::Server();
		break;
	}
	case Engine::Client:
	{
		connection = new Network::Client(host, port);
		break;
	}
	default:
		std::cout << "Invalid Connection Type";
		return;
	}

	if (connectionType == Client)
	{
		if (!ui.initialize("Client"))
		{
			std::cout << "Could not initialize UI" << std::endl;
		}
	}


}
void Engine::run()
{
	std::thread receiveThread(&NetworkConnection::receiveData, connection);
	std::thread sendThread(&NetworkConnection::start, connection);

	while (!connection->connected)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	if (connectionType == Engine::ConnectionType::Client)
	{
		playerId = connection->initialize();
	}

	while (running)
	{
		update();
	}

	connection->stop();
	sendThread.join();
	receiveThread.join();
	ui.cleanup(players, gameObjects);
}


void Engine::update()
{
	auto messageChannels = connection->getChannel().fetchReceivedData();
	ProcessReceivedData(messageChannels);

	SDL_Event event = ui.getInput();

	if (event.type == SDL_EVENT_QUIT)
	{
		running = false;
	}
	else if (event.type == SDL_EVENT_KEY_DOWN)
	{
		if (connectionType == ConnectionType::Server)
		{
			updateGameObjects(event);
			auto thing = Network::Message(Network::Message::Replication, serializeGameObjects(players));
			connection->getChannel().setDataToSend(thing);
		}
		else
		{
			updateGameObjects(event);
			auto thing = Network::Message(Network::Message::Replication, serializeGameObject(players[playerId]));
			connection->getChannel().setDataToSend(thing);
		}
	}

	ui.render(players, gameObjects);
}

void Engine::ProcessReceivedData(std::map<int, std::unordered_map<int, Network::Message>>& messageChannels)
{
	if (connectionType == ConnectionType::Server)
	{
		bool hit = false;
		for (auto& channel : messageChannels)
		{
			for (auto& message : channel.second)
			{
				if (message.second.getMessageType() == Network::Message::Hello)
				{
					hit = true;
					unsigned int playerId = 0;
					std::memcpy(&playerId, message.second.getPayload().data(), sizeof(unsigned int));
					players.insert_or_assign(playerId, Sprite(playerId, ui.loadTexture("./Player.bmp"), SDL_FRect{ spawnX, 100, 175, 100 }, 15));
					auto serializedPlayerId = std::vector<unsigned char>(sizeof(unsigned int));
					std::memcpy(serializedPlayerId.data(), &playerId, sizeof(unsigned int));
					auto thing = Network::Message(Network::Message::Hello, serializedPlayerId);
					connection->getChannel().setDataToSend(thing);
				}
				else
				{
					hit = true;
					auto player = deserializeGameObject(message.second.getPayload());
					players[player.id] = player;
					players[player.id].texture = ui.loadTexture("./Player.bmp");
				}

				connection->getChannel().removeFetchData(channel.first, message.first);
			}
		}
		if (hit)
		{
			auto thing = Network::Message(Network::Message::Replication, serializeGameObjects(players));
			connection->getChannel().setDataToSend(thing);
		}
	}
	else
	{
		for (auto& channel : messageChannels)
		{
			for (auto& message : channel.second)
			{
				if (message.second.getMessageType() == message.second.Replication)
				{
					players = deserializeGameObjects(message.second.getPayload());
					for (auto& player : players)
					{
						player.second = Sprite(player.second.id, ui.loadTexture("./Player.bmp"), player.second.boundingBox, player.second.moveStep);
					}
					connection->getChannel().removeFetchData(channel.first, message.first);
				}

			}
		}
	}
}

void Engine::updateGameObjects(SDL_Event event)
{
	switch (event.key.scancode)
	{
	case SDL_SCANCODE_UP:
		players[playerId].boundingBox.y -= players[playerId].moveStep;
		break;
	case SDL_SCANCODE_DOWN:
		players[playerId].boundingBox.y += players[playerId].moveStep;
		break;
	case SDL_SCANCODE_LEFT:
		players[playerId].boundingBox.x -= players[playerId].moveStep;
		break;
	case SDL_SCANCODE_RIGHT:
		players[playerId].boundingBox.x += players[playerId].moveStep;
		break;
	case SDL_SCANCODE_ESCAPE:
		running = false;
		break;
	}
}

std::vector<unsigned char> Engine::serializeGameObjects(const std::unordered_map<unsigned int, Sprite>& gameObjects)
{
	std::vector<unsigned char> serializedData;
	for (const auto& object : gameObjects)
	{
		size_t dataSize = sizeof(object.first) + sizeof(object.second.boundingBox) + sizeof(object.second.moveStep);
		std::vector<unsigned char> objData(dataSize);
		size_t offset = 0;
		std::memcpy(objData.data() + offset, &object.first, sizeof(object.first));
		offset += sizeof(object.first);
		std::memcpy(objData.data() + offset, &object.second.boundingBox, sizeof(object.second.boundingBox));
		offset += sizeof(object.second.boundingBox);
		std::memcpy(objData.data() + offset, &object.second.moveStep, sizeof(object.second.moveStep));
		offset += sizeof(object.second.moveStep);

		serializedData.insert(serializedData.end(), objData.begin(), objData.end());
	}
	return serializedData;
}

std::unordered_map<unsigned int, Sprite> Engine::deserializeGameObjects(const std::vector<unsigned char>& serializedGameObjects)
{
	std::unordered_map<unsigned int, Sprite> deserializedObjects;
	size_t offset = 0;

	while (offset < serializedGameObjects.size())
	{
		int id;
		std::memcpy(&id, &serializedGameObjects[offset], sizeof(int));
		offset += sizeof(int);

		SDL_FRect boundingBox;
		std::memcpy(&boundingBox, &serializedGameObjects[offset], sizeof(SDL_FRect));
		offset += sizeof(SDL_FRect);

		int moveStep;
		std::memcpy(&moveStep, &serializedGameObjects[offset], sizeof(int));
		offset += sizeof(int);

		// Add the deserialized object to the list
		deserializedObjects.insert({ id, Sprite(id, nullptr, boundingBox, moveStep) });
	}

	return deserializedObjects;
}

std::vector<unsigned char>Engine::serializeGameObject(Sprite object)
{
	size_t dataSize = sizeof(object.boundingBox) + sizeof(object.moveStep) + sizeof(object.id);
	std::vector<unsigned char> objData(dataSize);
	size_t offset = 0;
	std::memcpy(objData.data() + offset, &object.id, sizeof(object.id));
	offset += sizeof(object.id);
	std::memcpy(objData.data() + offset, &object.boundingBox, sizeof(object.boundingBox));
	offset += sizeof(object.boundingBox);
	std::memcpy(objData.data() + offset, &object.moveStep, sizeof(object.moveStep));
	return objData;
}

Sprite Engine::deserializeGameObject(std::vector<unsigned char> serializedGameObject)
{
	size_t offset = 0;

	// Deserialize one object
	int id;
	std::memcpy(&id, &serializedGameObject[offset], sizeof(int));
	offset += sizeof(int);

	// Deserialize one object
	SDL_FRect boundingBox;
	std::memcpy(&boundingBox, &serializedGameObject[offset], sizeof(SDL_FRect));
	offset += sizeof(SDL_FRect);

	int moveStep;
	std::memcpy(&moveStep, &serializedGameObject[offset], sizeof(int));

	return Sprite(id, nullptr, boundingBox, moveStep);

}


