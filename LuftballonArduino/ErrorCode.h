#ifndef ERRORCODE_H
#define ERRORCODE_H

#include <stdint.h>

//General error code enum.
enum class ErrorCode
{
	GeneralFailure,
	HeartbeatTimeout,
	NoPacketHandler,
	InvalidRequest
};

constexpr uint8_t ErrorCodePacketId = 2;

#endif