#ifndef MEMORYHANDLER_H
#define MEMORYHANDLER_H

#include "IPacketHandler.h"
#include "Util.h"

class MemoryHandler :
	public IPacketHandler
{
	uint8_t _packetId;

public:
	explicit MemoryHandler(const uint8_t packetId);
	void Setup() override;
	Packet HandlePacket(const Packet& packet) override;
};


inline MemoryHandler::MemoryHandler(const uint8_t packetId) : _packetId(packetId)
{

}

inline void MemoryHandler::Setup()
{

}

inline Packet MemoryHandler::HandlePacket(const Packet& packet)
{
	return Packet{ _packetId, freeMemory() };
}

#endif