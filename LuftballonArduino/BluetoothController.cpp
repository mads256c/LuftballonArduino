#include "BluetoothController.h"
#include "Util.h"
#include "PacketHandlers.h"

//Reads a command from the bluetooth module. buffer must be null initialized.
Packet BluetoothController::ReadPacket()
{
	if (!Serial.available())
		return Packet{ 0, 0 };

	while(Serial.read() != 0xFF) {}
	
	uint8_t buffer[9] = { 0 };

	Serial.readBytes(buffer, sizeof(buffer));

	//Serial.println(buffer[0]);

	uint64_t result = 0;
	for (byte i = 8; i >= 1; i--)
	{
		result <<= 8;
		result |= static_cast<uint64_t>(buffer[i]);
	}

	char buff[24] = { 0 };

	//Serial.println(uintToStr(result, buff));

	const Packet packet{ buffer[0], result };

	return packet;
}

void BluetoothController::HandlePacket(Packet& packet)
{
	if (PacketHandlers[packet.Id] == nullptr)
	{
		SendErrorPacket(ErrorCode::NoPacketHandler);
	}
	else
	{
		Packet response = PacketHandlers[packet.Id]->HandlePacket(packet);
		SendPacket(response);
	}
}

void BluetoothController::SendPacket(Packet& packet)
{

	//while (!softwareSerial.availableForWrite()) {}
	Serial.write(0xFF);

	Serial.write(packet.Id); //Send packet id

	//while (!softwareSerial.availableForWrite()) {}

	Serial.write(static_cast<uint8_t>(packet.Data & 0xFF)); //Send packet data
	Serial.write(static_cast<uint8_t>((packet.Data >> 8) & 0xFF));
	Serial.write(static_cast<uint8_t>((packet.Data >> 16) & 0xFF));
	Serial.write(static_cast<uint8_t>((packet.Data >> 24) & 0xFF));
	Serial.write(static_cast<uint8_t>((packet.Data >> 32) & 0xFF));
	Serial.write(static_cast<uint8_t>((packet.Data >> 40) & 0xFF));
	Serial.write(static_cast<uint8_t>((packet.Data >> 48) & 0xFF));
	Serial.write(static_cast<uint8_t>((packet.Data >> 56) & 0xFF));

}

void BluetoothController::SendErrorPacket(const ErrorCode errorCode)
{
	Packet packet{ ErrorCodePacketId, static_cast<uint64_t>(errorCode) };

	SendPacket(packet);
}

void BluetoothController::Setup(const uint32_t baudrate)
{
	Serial.begin(baudrate);
	AddPacketHandlers();
	InitializePacketHandlers();
}

void BluetoothController::Loop()
{
	Packet packet = ReadPacket();

	if (packet.Id != 0) // 0 in id means no data was received
		HandlePacket(packet);


	//SendErrorPacket(ErrorCode::NoPacketHandler);

	//softwareSerial.write(ErrorCodePacketId);
	//softwareSerial.write(1);
	//softwareSerial.write(2);
	//softwareSerial.write(3);
	//softwareSerial.write(4);
	//softwareSerial.write(5);
	//softwareSerial.write(6);
	//softwareSerial.write(7);
	//softwareSerial.write(8);
}
