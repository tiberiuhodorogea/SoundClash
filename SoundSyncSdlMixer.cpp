#include <SDL.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <SDL_mixer.h>
#include <iostream>
#include"ThreadPool.h"
#include"MusicPlayer.h"
#include<thread>
#include<chrono>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include"Message.h"
#include"Utils.h"
#include"LoadMessage.h"
#include"SyncMessage.h"
#include"Connection.h"
using namespace std::chrono_literals;

int main(int argc, char* argv[]) 
{
    //initializing
    MusicPlayer player;
    Connection connectionMaster(5555, L"192.168.0.196", player);
    connectionMaster.init();
    connectionMaster.socketAccept();

    //Initiizing default messages
    Message defaultMessage(Empty);
    LoadMessage defautlLoadMessage("defaultPath");
    SyncMessage defaultSyncMessage(0.0);
    std::string command;
    std::string messageSerialized=" ";

    while (std::cin >> command)
    {
        if (command == "load")
        {
            std::cin >> command;
            player.loadMusic(command);
            LoadMessage toSend(command);
            messageSerialized = toSend.Serialize();
            connectionMaster.Send(messageSerialized);
            
        }
        else if (command == "play")
        {
            Message toSend(Play);
            messageSerialized = toSend.Serialize();
            connectionMaster.Send(messageSerialized);
            player.playMusic();
        }
        else if(command == "stop")
        {
            Message toSend(Stop);
            messageSerialized = toSend.Serialize();
            connectionMaster.Send(messageSerialized);
            player.pauseMusic();
            player.setMusicPosition(0);

        }
        else if (command == "pause")
        {
            Message toSend(Pause);
            messageSerialized = toSend.Serialize();
            connectionMaster.Send(messageSerialized);
            player.pauseMusic();
        }
        else if (command == "exit")
        {
            Message toSend(Exit);
            messageSerialized = toSend.Serialize();
            connectionMaster.Send(messageSerialized);
            break;
        }
        else if (command == "resume")
        {
            Message toSend(Resume);
            messageSerialized = toSend.Serialize();
            connectionMaster.Send(messageSerialized);
        }
        else
        {
            std::cout << "Wrong command!" << std::endl;
        }
        
    }
    std::cout << "Exiting program..." << std::endl;

    //Uninitializing
    connectionMaster.uninit();
    player.uninitMusicPlayer();

   //if (SDL_Init(SDL_INIT_AUDIO) < 0) {
   //     printf("Failed to initialize SDL: %s\n", SDL_GetError());
   //     return -1;
   // }

   // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
   //     printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
   //     SDL_Quit();
   //     return -1;
   // }
   // listAudioDevices();
	return 0;
}
