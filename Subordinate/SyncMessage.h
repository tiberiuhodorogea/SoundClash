#pragma once
#include"Message.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include <chrono>
#include"MusicPlayer.h"
class SyncMessage : public Message
{

private:
	double _songTime;
	long long _realTime;
public:

	SyncMessage(double songTime);
	std::string Serialize();
	static SyncMessage Deserialize(const std::string& JSONObject);
	long long getRealTime();

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::make_nvp("_songTime", _songTime),cereal::make_nvp("_realTime", _realTime), cereal::make_nvp("_type", _type));
	}
};