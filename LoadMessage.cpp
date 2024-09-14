#pragma once
#include"LoadMessage.h"
#include"Utils.h"
LoadMessage::LoadMessage(std::string path)
{
	_path = path;
	_type = Load;
}
LoadMessage::LoadMessage()
{
	
}

std::string LoadMessage::Serialize()
{
	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(*this);
	}
	return ss.str();
}

std::string LoadMessage::getPath()
{
	return  _path;
}

LoadMessage LoadMessage::Deserialize(const std::string& JSONObject)
{
	LoadMessage ret("path");
	std::stringstream ss(JSONObject);
	cereal::JSONInputArchive iarchive(ss);
	iarchive(ret);
	return ret;
}


