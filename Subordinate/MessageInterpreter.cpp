#include "MessageInterpreter.h"

void MessageInterpreter::interpretAndExecute(std::string message)
{
	Message defaultMessage(Empty);  
    defaultMessage = Message::Deserialize(message);
    LoadMessage loadMessageDefault("Default Path");
    SyncMessage syncMessageDefault(0.0);
    //sync
    switch (defaultMessage.GetType())
    {
    case Load:
        loadMessageDefault = LoadMessage::Deserialize(message);
        _player->loadMusic(loadMessageDefault.getPath());
        std::cout << loadMessageDefault.getPath() << " Loaded " << std::endl;
        break;
    case Pause:
        std::cout << "Music paused" << std::endl;
        _player->pauseMusic();
        break;
    case Stop:
        std::cout << "Music stopped" << std::endl;
        _player->pauseMusic();
        _player->setMusicPosition(0);
        break;
        std::cout << "Exiting program" << std::endl;
    case Exit:
        break;
    case Resume:
        std::cout << "Resuming..." << std::endl;
        _player->ResumeMusic();
        break;
    case Play:
        std::cout << "playing...";
        _player->playMusic();
        break;
    case Sync:
        std::cout << "This feature is not implemented yet!" << std::endl;
        syncMessageDefault = SyncMessage::Deserialize(message);
        break;
    default:
        std::cout << "Error";
        break;
    }
	

}
MessageInterpreter::MessageInterpreter(MusicPlayer* player)
{
	_player = player;
}