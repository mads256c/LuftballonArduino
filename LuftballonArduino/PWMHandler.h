#ifndef PWMHANDLER_H
#define PWMHANDLER_H

#include "IPacketHandler.h"
#include "Arduino.h"

//Does not work when a servo is in use.
class PWMHandler :
	public IPacketHandler
{
	const uint8_t _pwmPin;

public:
	PWMHandler(const uint8_t pwmPin);
	void Setup() override;
	Packet HandlePacket(const Packet& packet) override;
};



PWMHandler::PWMHandler(const uint8_t pwmPin) : _pwmPin(pwmPin)
{
}

inline void PWMHandler::Setup()
{
	pinMode(_pwmPin, OUTPUT);
}

inline Packet PWMHandler::HandlePacket(const Packet& packet)
{
	analogWrite(_pwmPin, packet.Data.u64);

	return NoopPacket;
}

#endif
