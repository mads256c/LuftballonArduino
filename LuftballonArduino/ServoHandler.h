#ifndef SERVOHANDLER_H
#define SERVOHANDLER_H

#include "IPacketHandler.h"
#include <stdint.h>
#include <Servo.h>

class ServoHandler final :
	public IPacketHandler
{

	Servo _servo;
	const uint8_t _servoPin;

public:
	explicit ServoHandler(const uint8_t servoPin);
	void Setup() override;
	Packet HandlePacket(const Packet& packet) override;
};


inline ServoHandler::ServoHandler(const uint8_t servoPin) : _servoPin(servoPin)
{

}

inline void ServoHandler::Setup()
{
	_servo.attach(_servoPin);
}

inline Packet ServoHandler::HandlePacket(const Packet& packet)
{
	_servo.write(packet.Data.i16[0]);

	return NoopPacket;
}


#endif
