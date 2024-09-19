#pragma once
#include "MusicPlayer.h"
#include"Message.h"
#include"LoadMessage.h"
#include"SyncMessage.h"
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
class MessageInterpreter
{
private:
	MusicPlayer* _player;
public:
	MessageInterpreter(MusicPlayer* player);
	void interpretAndExecute(std::string message);

};