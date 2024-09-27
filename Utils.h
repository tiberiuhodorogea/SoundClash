#pragma once
#include <chrono>
enum MessageType {
	Empty,Load, Pause, Stop, Sync, Exit,Play,Resume
};

inline long long getRealTime()
{
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}