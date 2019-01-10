#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include "Packet.h"
#include "ErrorCode.h"

class BluetoothController
{
private:

	Packet ReadPacket() const;
	void HandlePacket(const Packet &packet) const;

	void SendPacket(const Packet &packet) const;
	void SendErrorPacket(const ErrorCode errorCode) const;

public:

	void Setup(const uint32_t baudrate) const;
	void Loop() const;
};

#endif