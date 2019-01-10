#ifndef PACKETHANDLERS_H
#define PACKETHANDLERS_H

#include <Arduino.h>
#include "IPacketHandler.h"
#include "OnOffHandler.h"
#include "ServoHandler.h"
#include "HeartbeatHandler.h"
#include "AnalogReadHandler.h"
#include "UltraSonicHandler.h"
#include "MemoryHandler.h"

#define DEFINE_PACKETHANDLER(id, objectPointer) PacketHandlers[id] = objectPointer

IPacketHandler* PacketHandlers[256] = { nullptr };

inline void AddPacketHandlers()
{
	DEFINE_PACKETHANDLER(3, new HeartbeatHandler());
	DEFINE_PACKETHANDLER(4, new OnOffHandler(LED_BUILTIN, LOW)); //BuiltIn LED on pin 13
	DEFINE_PACKETHANDLER(5, new ServoHandler(3));
	DEFINE_PACKETHANDLER(6, new AnalogReadHandler(6, A0, A1));
	DEFINE_PACKETHANDLER(7, new UltraSonicHandler(7, 8, 9));
	DEFINE_PACKETHANDLER(8, new MemoryHandler(8));
}

inline void InitializePacketHandlers()
{
	for (IPacketHandler* const packetHandler : PacketHandlers)
	{
		if (packetHandler != nullptr) packetHandler->Setup();
	}
}

#undef DEFINE_PACKETHANDLER

#endif