#pragma once
#ifndef PACKETHANDLERS_H
#define PACKETHANDLERS_H

#include "Packet.h"
#include "Arduino.h"
#include "IPacketHandler.h"
#include "OnOffHandler.h"
#include "ServoHandler.h"
#include "HeartbeatHandler.h"
#include "AnalogReadHandler.h"

#define DEFINE_PACKETHANDLER(id, constructer) PacketHandlers[id] = new constructer

IPacketHandler* PacketHandlers[256] = { nullptr };

inline void AddPacketHandlers()
{
	DEFINE_PACKETHANDLER(3, HeartbeatHandler());
	DEFINE_PACKETHANDLER(4, OnOffHandler(LED_BUILTIN, LOW)); //BuiltIn LED on pin 13
	DEFINE_PACKETHANDLER(5, ServoHandler(3));
	DEFINE_PACKETHANDLER(6, AnalogReadHandler(6, A0, A1));
}

inline void InitializePacketHandlers()
{
	for (IPacketHandler* packetHandler : PacketHandlers)
	{
		if (packetHandler != nullptr) packetHandler->Setup();
	}
}

#endif