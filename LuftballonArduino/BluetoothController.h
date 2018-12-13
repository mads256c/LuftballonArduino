#pragma once
#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "Packet.h"
#include "ErrorCode.h"

class BluetoothController
{
private:
	//SoftwareSerial softwareSerial;

	unsigned long lastHeartbeat = 0;

	const unsigned long heartbeatInterval = 1000;

	Packet ReadPacket();
	void HandlePacket(Packet &packet);

	void SendPacket(Packet &packet);
	void SendErrorPacket(ErrorCode errorCode);

public:

	void Setup(const uint32_t baudrate);
	void Loop();


	~BluetoothController() = default;
};

#endif