#pragma once
#include <condition_variable>
#include <mutex>
#include <optional>
#include <vector>
#include <enet.h>
#include <map>
#include <iostream>
#include "Message.h" 
#include <unordered_map>

class ThreadSafeByteChannel
{
public:
	ThreadSafeByteChannel() : dataToSend(), messageChannels()
	{
	}
	void setDataToSend(Network::Message data)
	{
		std::lock_guard<std::mutex> lock(sendDataMtx);
		dataToSend.insert({ id++, data });  // Copy data to the vector
		cvSend.notify_one();
	}

	std::unordered_map<int, Network::Message> fetchSendData()
	{
		std::lock_guard<std::mutex> lock(sendDataMtx);
		return dataToSend;
	}

	void removeSendData(int id)
	{
		std::lock_guard<std::mutex> lock(sendDataMtx);
		dataToSend.erase(id);
	}

	void setReceivedData(int peerChannelId, Network::Message data)
	{
		std::lock_guard<std::mutex> lock(receviedDataMtx);
		messageChannels[peerChannelId].insert({ id++, data });
		cvReceived.notify_one();
	}

	void removeFetchData(int peerId, int messageId)
	{
		std::lock_guard<std::mutex> lock(sendDataMtx);
		messageChannels[peerId].erase(messageId);
	}

	std::map<int, std::unordered_map<int, Network::Message>> fetchReceivedData()
	{
		std::lock_guard<std::mutex> lock(receviedDataMtx);
		return messageChannels;
	}

	void addMessageChannel(int peerChannelId)
	{
		std::lock_guard<std::mutex> lock(receviedDataMtx);
		messageChannels[peerChannelId] = std::unordered_map<int, Network::Message>();
	}

	void removeMessageChannel(int peerChannelId)
	{
		std::lock_guard<std::mutex> lock(receviedDataMtx);
		messageChannels.erase(peerChannelId);
	}


	std::vector<ENetPeer*> peers;
private:
	std::map<int, std::unordered_map<int, Network::Message>> messageChannels;
	std::mutex receviedDataMtx;

	std::unordered_map<int, Network::Message> dataToSend;
	std::mutex sendDataMtx;

	int id = 0;

	std::condition_variable cvReceived;
	std::condition_variable cvSend;
};