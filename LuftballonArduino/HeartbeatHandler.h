#ifndef HEARTBEATHANDLER_H
#define HEARTBEATHANDLER_H

#include "IPacketHandler.h"
class HeartbeatHandler final :
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

#endif