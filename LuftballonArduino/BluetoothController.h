#pragma once

#include <SoftwareSerial.h>
#include "Packet.h"
#include "ErrorCode.h"

class BluetoothController
{
private:
	SoftwareSerial softwareSerial;

	unsigned long lastHeartbeat = 0;

	const unsigned long heartbeatInterval = 1000;

	Packet ReadPacket();
	void HandlePacket(Packet &packet);

	void SendPacket(Packet &packet);
	void SendErrorPacket(ErrorCode errorCode);

public:
	BluetoothController(const uint8_t receivePin, const uint8_t transmitPin);

	void Setup(uint32_t baudrate);
	void Loop();


	~BluetoothController() = default;
};

