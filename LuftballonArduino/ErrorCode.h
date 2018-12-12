#pragma once

enum class ErrorCode
{
	GeneralFailure,
	HeartbeatTimeout,
	NoPacketHandler,
};

constexpr char ErrorCodePacketId = 2;