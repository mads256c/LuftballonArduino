#include "BluetoothController.h"
#include "Util.h"
#include "PacketHandlers.h"

//Reads a command from the bluetooth module. buffer must be null initialized.
Packet BluetoothController::ReadPacket()
{
	uint8_t buffer[9] = {0};

	if (softwareSerial.available())
	{
		softwareSerial.readBytes(buffer, sizeof(buffer));

		Serial.println(buffer[0]);

		uint64_t result = 0;
		for (int i = 8; i >= 1; i--)
		{
			result <<= 8;
			result |= (uint64_t)buffer[i];
		}

		char buff[24] = { 0 };

		Serial.println(uintToStr(result, buff));

	}



	const Packet packet{ buffer[0], 0 };

	return packet;

}

void BluetoothController::HandlePacket(Packet& packet)
{
	Packet response{0, 0};
	switch (packet.Id)
	{
		DEFINE_PACKETHANDLER(1, HandleTestPacket);
	default:
		SendErrorPacket(ErrorCode::NoPacketHandler);
		break;
	}
}

void BluetoothController::SendPacket(Packet& packet)
{
	char buffer[24] = { 0 };

	if (softwareSerial.availableForWrite())
	{
		softwareSerial.write(packet.Id); //Send packet id
		softwareSerial.write(uintToStr(packet.Data, buffer)); //Send packet data
		softwareSerial.write(' '); //End packet
	}
}

void BluetoothController::SendErrorPacket(const ErrorCode errorCode)
{
	Packet packet{ ErrorCodePacketId, static_cast<uint64_t>(errorCode) };

	SendPacket(packet);
}

BluetoothController::BluetoothController(const uint8_t receivePin, const uint8_t transmitPin) : softwareSerial(receivePin, transmitPin)
{

}


void BluetoothController::Setup(const uint32_t baudrate)
{
	softwareSerial.begin(baudrate);
}

void BluetoothController::Loop()
{
	Packet packet = ReadPacket();
	HandlePacket(packet);
}
