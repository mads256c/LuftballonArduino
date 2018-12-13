#pragma once

enum class ErrorCode
{
	GeneralFailure,
	HeartbeatTimeout,
	NoPacketHandler,
	InvalidRequest
};

constexpr char ErrorCodePacketId = 2;