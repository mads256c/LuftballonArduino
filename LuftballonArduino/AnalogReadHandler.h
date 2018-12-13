#pragma once
#include "IPacketHandler.h"
#include "Arduino.h"
class AnalogReadHandler :
	public IPacketHandler
{
	const uint8_t _packetId;
	const uint8_t _pin1;
	const uint8_t _pin2;

public:
	AnalogReadHandler(const uint8_t packetId, const uint8_t pin1, const uint8_t pin2);
	void Setup() override;
	Packet HandlePacket(const Packet& packet) override;
};



AnalogReadHandler::AnalogReadHandler(const uint8_t packetId, const uint8_t pin1, const uint8_t pin2) : _packetId(packetId),_pin1(pin1), _pin2(pin2)
{
}

inline void AnalogReadHandler::Setup()
{
}

inline Packet AnalogReadHandler::HandlePacket(const Packet& packet)
{
	uint64_t data;

	switch (packet.Data)
	{
	case 0:
		{
		data = analogRead(_pin1);
		const uint64_t p2 = analogRead(_pin2);

		data |= (p2 << 32);
		}
		break;

	case 1:
		data = analogRead(_pin1);
		break;

	case 2:

		data = analogRead(_pin2);
		break;

	default:
		const Packet retPacket{ ErrorCodePacketId, static_cast<uint64_t>(ErrorCode::InvalidRequest) };
		return retPacket;
		
	}

	const Packet retPacket{ _packetId, data };
	return retPacket;
}
