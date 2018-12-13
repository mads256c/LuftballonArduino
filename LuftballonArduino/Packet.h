#pragma once
#ifndef PACKET_H
#define PACKET_H
#include "Arduino.h"

struct Packet
{
	uint8_t Id;
	uint64_t Data;
};

constexpr Packet NoopPacket{ 1, 0 };

#endif