#pragma once
#ifndef ONOFFHANDLER_H
#define ONOFFHANDLER_H

#include "IPacketHandler.h"
#include "Arduino.h"

class OnOffHandler :
	public IPacketHandler
{
	const uint8_t _pin;
	const uint8_t _initialState;

public:
	explicit OnOffHandler(const uint8_t pin, const uint8_t initialState);
	void Setup() override;
	Packet HandlePacket(const Packet& packet) override;
};

inline OnOffHandler::OnOffHandler(const uint8_t pin, const uint8_t initialState) : _pin(pin), _initialState(initialState)
{
}

inline void OnOffHandler::Setup()
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, _initialState);
}

inline Packet OnOffHandler::HandlePacket(const Packet& packet)
{
	if (packet.Data)
		digitalWrite(LED_BUILTIN, HIGH);
	else
		digitalWrite(LED_BUILTIN, LOW);

	return NoopPacket;
}

#endif