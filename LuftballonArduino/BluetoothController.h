#ifndef BLUETOOTHCONTROLLER_H
#define BLUETOOTHCONTROLLER_H

#include "Arduino.h"
//#include <SoftwareSerial.h>
#include "Packet.h"
#include "ErrorCode.h"

class BluetoothController
{
private:

	Packet ReadPacket();
	void HandlePacket(Packet &packet);

	void SendPacket(Packet &packet);
	void SendErrorPacket(ErrorCode errorCode);

public:

	void Setup(const uint32_t baudrate) const;
	void Loop();
};

#endif