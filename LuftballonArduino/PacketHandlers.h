#pragma once
#ifndef PACKETHANDLERS_H
#define PACKETHANDLERS_H

#include "Packet.h"
#include "Arduino.h"
#include "IPacketHandler.h"
#include "LedHandler.h"
#include "ServoHandler.h"

#define DEFINE_PACKETHANDLER(id, constructer) PacketHandlers[id] = new constructer

IPacketHandler* PacketHandlers[256] = { nullptr };

inline void AddPacketHandlers()
{
	DEFINE_PACKETHANDLER(4, LedHandler(LED_BUILTIN));
	DEFINE_PACKETHANDLER(5, ServoHandler(5));
}

inline void InitializePacketHandlers()
{
	for (IPacketHandler* packetHandler : PacketHandlers)
	{
		if (packetHandler != nullptr) packetHandler->Setup();
	}
}

#endif