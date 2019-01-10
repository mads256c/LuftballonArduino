#ifndef ERRORCODE_H
#define ERRORCODE_H

enum class ErrorCode
{
	GeneralFailure,
	HeartbeatTimeout,
	NoPacketHandler,
	InvalidRequest
};

constexpr char ErrorCodePacketId = 2;

#endif