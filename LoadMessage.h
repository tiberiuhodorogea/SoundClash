#pragma once
#include<string>
#include"Message.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>

class LoadMessage : public Message
{
private:
	std::string _path;
public:

	LoadMessage(std::string path); //Constructor
	std::string Serialize();
	static LoadMessage Deserialize(const std::string& JSONObject);
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::make_nvp("_path", _path), cereal::make_nvp("_type", _type));
	}
	std::string getPath();

	
};