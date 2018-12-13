#pragma once
#include "IPacketHandler.h"
class HeartbeatHandler :
	public IPacketHandler
{
public:
	void Setup() override;
	Packet HandlePacket(const Packet& packet) override;
};

inline void HeartbeatHandler::Setup()
{

}

inline Packet HeartbeatHandler::HandlePacket(const Packet& packet)
{
	return Packet{ 3, millis() };
}



