#ifndef ANALOGREADHANDLER_H
#define ANALOGREADHANDLER_H
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
	Packet::PacketData data{};
	data.u64 = 0;

	switch (packet.Data.u64)
	{
	case 0:
		data.i16[0] = analogRead(_pin1);
		data.i16[1] = analogRead(_pin2);
		break;

	case 1:
		data.i16[0] = analogRead(_pin1);
		break;

	case 2:
		data.i16[0] = analogRead(_pin2);
		break;

	default:
		const Packet retPacket{ ErrorCodePacketId, static_cast<uint64_t>(ErrorCode::InvalidRequest) };
		return retPacket;
		
	}

	const Packet retPacket{ _packetId, data };
	return retPacket;
}

#endif