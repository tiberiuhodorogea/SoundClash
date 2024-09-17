#include "MessageInterpreter.h"

void MessageInterpreter::interpretAndExecute(std::string message)
{
	Message defaultMessage(Empty);
	defaultMessage=Message::Deserialize(message);
    LoadMessage loadMessageDefault("Default Path");
    //sync
    switch (defaultMessage.GetType())
    {
    case Load:
        loadMessageDefault = LoadMessage::Deserialize(message);
        _player->loadMusic(loadMessageDefault.getPath());
        break;
    case Pause:
        _player->pauseMusic();
        break;
    case Stop:
        _player->pauseMusic();
        _player->setMusicPosition(0);
        break;
    case Exit:
        
        break;
    case Resume:
        _player->ResumeMusic();
        break;
    case Play:
        _player->playMusic();
        break;
    default:
        
        break;
    }
	

}
MessageInterpreter::MessageInterpreter(MusicPlayer* player)
{
	_player = player;
}