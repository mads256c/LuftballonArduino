#pragma once
#ifndef LEDHANDLER_H
#define LEDHANDLER_H

#include "IPacketHandler.h"
#include "Arduino.h"

class LedHandler :
	public IPacketHandler
{
	const uint8_t _ledPin;

public:
	explicit LedHandler(const uint8_t ledPin);
	void Setup() override;
	Packet HandlePacket(Packet& packet) override;
};

inline LedHandler::LedHandler(const uint8_t ledPin) : _ledPin(ledPin)
{
}

inline void LedHandler::Setup()
{
	pinMode(_ledPin, OUTPUT);
	digitalWrite(_ledPin, LOW);
}

inline Packet LedHandler::HandlePacket(Packet& packet)
{
	if (packet.Data)
		digitalWrite(LED_BUILTIN, HIGH);
	else
		digitalWrite(LED_BUILTIN, LOW);

	return NoopPacket;
}

#endif