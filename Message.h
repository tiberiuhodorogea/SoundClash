#pragma once
#include "Utils.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
class Message 
{
public:
	Message(MessageType Type=Empty);  

	static Message Deserialize(const std::string& JSONObject);

	//Getters
	std::string Serialize();
	MessageType GetType() const
	{
		return _type;
	}
	

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::make_nvp("_type", _type));
	}
	
protected:
	MessageType _type;
};

