#include "BluetoothController.h"
#include "Util.h"
#include "PacketHandlers.h"

//Reads a command from the bluetooth module.
Packet BluetoothController::ReadPacket() const
{
	if (!Serial.available())
		return Packet{ 0, 0 };

	while(Serial.read() != 0xFF) {}
	
	uint8_t buffer[9] = { 0 };

	Serial.readBytes(buffer, sizeof(buffer));

	Packet::PacketData data{};
	for (uint8_t i = 0; i < 8; i++)
	{
		data.u8[i] = buffer[i + 1];
	}

	const Packet packet{ buffer[0], data };

	return packet;
}

void BluetoothController::HandlePacket(const Packet& packet) const
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

void BluetoothController::SendPacket(const Packet& packet) const
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

void BluetoothController::SendErrorPacket(const ErrorCode errorCode) const
{
	Packet packet{ ErrorCodePacketId, static_cast<uint64_t>(errorCode) };

	SendPacket(packet);
}

void BluetoothController::Setup(const uint32_t baudrate) const
{
	Serial.begin(baudrate);
	AddPacketHandlers();
	InitializePacketHandlers();
}

void BluetoothController::Loop() const
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
