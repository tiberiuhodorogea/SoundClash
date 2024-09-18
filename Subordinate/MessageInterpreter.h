#pragma once
#include "MusicPlayer.h"
#include"Message.h"
#include"LoadMessage.h"
#include"SyncMessage.h"

class MessageInterpreter
{
private:
	MusicPlayer* _player;
public:
	MessageInterpreter(MusicPlayer* player);
	void interpretAndExecute(std::string message);

};