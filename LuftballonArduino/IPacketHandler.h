#ifndef IPACKETHANDLER_H
#define IPACKETHANDLER_H

#include "Packet.h"
//Base interface for packet handlers.
class IPacketHandler
{
	

public:

	//Initializes the Packethandler
	virtual void Setup() = 0;

	//Handles the packet
	virtual Packet HandlePacket(const Packet& packet) = 0;
};

#endif