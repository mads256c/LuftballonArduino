#pragma once
#ifndef ULTRASONICHANDLER_H
#define ULTRASONICHANDLER_H
#include "Arduino.h"
#include "IPacketHandler.h"


class UltraSonicHandler :
	public IPacketHandler
{
	const uint8_t _id;

	const uint8_t _echo;
	const uint8_t _trig;

public:
	UltraSonicHandler(const uint8_t id, const uint8_t echo, const uint8_t trig);
	void Setup() override;
	Packet HandlePacket(const Packet& packet) override;
};


inline UltraSonicHandler::UltraSonicHandler(const uint8_t id, const uint8_t echo, const uint8_t trig) : _id(id), _echo(echo), _trig(trig)
{
}

inline void UltraSonicHandler::Setup()
{
	pinMode(_echo, INPUT);
	pinMode(_trig, OUTPUT);
}

inline Packet UltraSonicHandler::HandlePacket(const Packet& packet)
{
	digitalWrite(_trig, LOW);
	delayMicroseconds(2);
	digitalWrite(_trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trig, LOW);

	return Packet{ _id, pulseIn(_echo, HIGH, 20000UL) };
}

#endif
