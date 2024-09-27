#include "SyncMessage.h"
#include"MusicPlayer.h"



SyncMessage::SyncMessage(double songTime)
{
	_songTime = songTime;
	_realTime = getRealTime();
	_type = Sync;
}

SyncMessage SyncMessage::Deserialize(const std::string& JSONObject)
{
	SyncMessage ret(1);
	std::stringstream ss(JSONObject);
	cereal::JSONInputArchive iarchive(ss);
	iarchive(ret);
	return ret;
}

std::string SyncMessage::Serialize()
{
	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(*this);
	}
	return ss.str();
}
