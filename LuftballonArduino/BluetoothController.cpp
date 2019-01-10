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

	Serial.write(packet.Data.u8[0]); //Send packet data
	Serial.write(packet.Data.u8[1]);
	Serial.write(packet.Data.u8[2]);
	Serial.write(packet.Data.u8[3]);
	Serial.write(packet.Data.u8[4]);
	Serial.write(packet.Data.u8[5]);
	Serial.write(packet.Data.u8[6]);
	Serial.write(packet.Data.u8[7]);

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
