#pragma once
#include "Packet.h"
#include "Arduino.h"

#define DEFINE_PACKETHANDLER(id, func) case id : {response = func(packet);} break


Packet HandleTestPacket(Packet& packet)
{
	Serial.println("LOLXD");

	return Packet{1, packet.Data};
}

Packet HandleLedPacket(Packet& packet)
{
	if (packet.Data)
		digitalWrite(LED_BUILTIN, HIGH);
	else
		digitalWrite(LED_BUILTIN, LOW);

	return NoopPacket;
}