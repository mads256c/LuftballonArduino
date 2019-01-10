#ifndef SERVOHANDLER_H
#define SERVOHANDLER_H

#include "IPacketHandler.h"
#include "Arduino.h"
#include <Servo.h>

class ServoHandler :
	public IPacketHandler
{

	Servo _servo;
	const uint8_t _servoPin;

public:
	ServoHandler(const uint8_t servoPin);
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
	_servo.write(packet.Data.u64);

	return NoopPacket;
}


#endif
