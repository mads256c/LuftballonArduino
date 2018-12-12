#pragma once

struct Packet
{
	char Id;
	uint64_t Data;
};

constexpr Packet NoopPacket{ 1, 0 };