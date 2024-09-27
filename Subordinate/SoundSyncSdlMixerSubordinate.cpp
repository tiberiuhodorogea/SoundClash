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
#include"MessageInterpreter.h"
using namespace std::chrono_literals;

int main(int argc, char* argv[]) 
{
    //initializing
    MusicPlayer player;
    MessageInterpreter interpreter(&player);
    Connection connectionSubordinate(5555, L"192.168.0.197",&interpreter);
    connectionSubordinate.init();
    connectionSubordinate.startListening();

    //Exiting program
    std::cout << "Exiting program..." << std::endl;

    //Uninitializing
    connectionSubordinate.uninit();
    player.uninit();
	return 0;
}
