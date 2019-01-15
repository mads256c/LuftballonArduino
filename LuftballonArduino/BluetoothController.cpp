#include "BluetoothController.h"
#include "PacketHandlers.h"

//Reads a command from the bluetooth module.
Packet BluetoothController::ReadPacket() const
{
	if (!Serial.available())
		return Packet{ 0, 0 };

	//Wait until we read the packet preamble. This is not perfect, but it should synchronize the packets.
	while(Serial.read() != 0xFF) {}
	
	uint8_t buffer[9] = { 0 };

	Serial.readBytes(buffer, sizeof(buffer));

	Packet::PacketData data{};

	data.u8[0] = buffer[1];
	data.u8[1] = buffer[2];
	data.u8[2] = buffer[3];
	data.u8[3] = buffer[4];
	data.u8[4] = buffer[5];
	data.u8[5] = buffer[6];
	data.u8[6] = buffer[7];
	data.u8[7] = buffer[8];

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
		const Packet response = PacketHandlers[packet.Id]->HandlePacket(packet);
		SendPacket(response);
	}
}

void BluetoothController::SendPacket(const Packet& packet) const
{


	Serial.write(0xFF); //Send packet preamble

	Serial.write(packet.Id); //Send packet id


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
	const Packet packet{ ErrorCodePacketId, static_cast<uint64_t>(errorCode) };

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
	const Packet packet = ReadPacket();

	if (packet.Id != 0) // 0 in id means no data was received
		HandlePacket(packet);

}
