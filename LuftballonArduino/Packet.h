#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

struct Packet final
{
	union PacketData final
	{
		uint64_t u64;
		uint32_t u32[2];
		uint16_t u16[4];
		uint8_t u8[8];

		int64_t i64;
		int32_t i32[2];
		int16_t i16[4];
		int8_t i8[8];

		//double d; //We cant do double on the arduino uno
		float f[2];

		static_assert(sizeof(u64) == 8, "u64 is not 8 bytes long");
		static_assert(sizeof(u32) == 8, "u32 is not 8 bytes long");
		static_assert(sizeof(u16) == 8, "u16 is not 8 bytes long");
		static_assert(sizeof(u8) == 8, "u8 is not 8 bytes long");

		static_assert(sizeof(i64) == 8, "i64 is not 8 bytes long");
		static_assert(sizeof(i32) == 8, "i32 is not 8 bytes long");
		static_assert(sizeof(i16) == 8, "i16 is not 8 bytes long");
		static_assert(sizeof(i8) == 8, "i8 is not 8 bytes long");

		//static_assert(sizeof(d) == 8, "d is not 8 bytes long");
		static_assert(sizeof(f) == 8, "f is not 8 bytes long");
	};

	static_assert(sizeof(PacketData) == 8, "Data is not 8 bytes long");

	uint8_t Id;
	PacketData Data;
};

static_assert(sizeof(Packet) == 9, "Packet is not 9 bytes long");



constexpr Packet NoopPacket{ 1, 0 };

#endif