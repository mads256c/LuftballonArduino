#pragma once
#include "Packet.h"
#include "Arduino.h"

#define DEFINE_PACKETHANDLER(id, func) case id : {response = func(packet);} break


Packet HandleTestPacket(Packet& packet)
{
	Serial.println("LOLXD");

	return Packet{1, packet.Data};
}
