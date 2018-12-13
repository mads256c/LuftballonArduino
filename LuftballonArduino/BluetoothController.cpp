#include "BluetoothController.h"
#include "Util.h"
#include "PacketHandlers.h"

//Reads a command from the bluetooth module. buffer must be null initialized.
Packet BluetoothController::ReadPacket()
{
	if (!softwareSerial.available())
		return Packet{ 0, 0 };

	while(softwareSerial.read() != 0xFF) {}
	
	uint8_t buffer[9] = { 0 };

	softwareSerial.readBytes(buffer, sizeof(buffer));

	Serial.println(buffer[0]);

	uint64_t result = 0;
	for (byte i = 8; i >= 1; i--)
	{
		result <<= 8;
		result |= static_cast<uint64_t>(buffer[i]);
	}

	char buff[24] = { 0 };

	Serial.println(uintToStr(result, buff));

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
	softwareSerial.write(0xFF);

	softwareSerial.write(packet.Id); //Send packet id

	//while (!softwareSerial.availableForWrite()) {}

	softwareSerial.write(static_cast<uint8_t>(packet.Data & 0xFF)); //Send packet data
	softwareSerial.write(static_cast<uint8_t>((packet.Data >> 8) & 0xFF));
	softwareSerial.write(static_cast<uint8_t>((packet.Data >> 16) & 0xFF));
	softwareSerial.write(static_cast<uint8_t>((packet.Data >> 24) & 0xFF));
	softwareSerial.write(static_cast<uint8_t>((packet.Data >> 32) & 0xFF));
	softwareSerial.write(static_cast<uint8_t>((packet.Data >> 40) & 0xFF));
	softwareSerial.write(static_cast<uint8_t>((packet.Data >> 48) & 0xFF));
	softwareSerial.write(static_cast<uint8_t>((packet.Data >> 56) & 0xFF));

}

void BluetoothController::SendErrorPacket(const ErrorCode errorCode)
{
	Packet packet{ ErrorCodePacketId, static_cast<uint64_t>(errorCode) };

	char buffer[24] = { 0 };

	Serial.println(uintToStr(packet.Data, buffer));
	
	SendPacket(packet);
}

BluetoothController::BluetoothController(const uint8_t receivePin, const uint8_t transmitPin) : softwareSerial(receivePin, transmitPin)
{

}


void BluetoothController::Setup(const uint32_t baudrate)
{
	softwareSerial.begin(baudrate);
	AddPacketHandlers();
	InitializePacketHandlers();
}

void BluetoothController::Loop()
{
	Packet packet = ReadPacket();

	if (packet.Id != 0) // 0 in id means no data was received
		HandlePacket(packet);

	const auto currentTime = millis();

	if (currentTime - lastHeartbeat > heartbeatInterval)
	{
		Packet heartbeatPacket{ 3, currentTime };
		SendPacket(heartbeatPacket);

		lastHeartbeat = currentTime;
	}


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
