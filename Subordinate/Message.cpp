#pragma once
#include"Message.h"
#include<string>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
Message::Message(MessageType Type)
{
	_type = Type;
}

Message Message::Deserialize(const std::string& JSONObject)
{
	Message ret(MessageType::Load);
	std::stringstream ss(JSONObject);
	cereal::JSONInputArchive iarchive(ss);
	iarchive(ret);
	return ret;
}

std::string Message::Serialize()
{
	std::stringstream ss;
	{
		cereal::JSONOutputArchive archive(ss);
		archive(*this);
	}
	return ss.str();  
}


