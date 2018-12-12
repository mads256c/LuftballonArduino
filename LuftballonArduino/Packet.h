#pragma once

struct Packet
{
	uint8_t Id;
	uint64_t Data;
};

constexpr Packet NoopPacket{ 1, 0 };