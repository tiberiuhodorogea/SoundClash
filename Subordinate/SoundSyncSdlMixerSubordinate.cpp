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

int main(int argc, char* argv[]) {
	/*Message Message1(MessageType::Exit); 
	std::string serializedData = Message1.Serialize();
	Message deserializedMessage=Message::Deserialize(serializedData);
	std::cout << "Serialized Message: " << serializedData << std::endl;
	std::cout << "Deserialized Message: " << deserializedMessage.GetType() << std::endl;*/

    //LoadMessage Message2("");
    //std::string serializedData2 = Message2.Serialize();
    //LoadMessage deserializedMessage2 = LoadMessage::Deserialize(serializedData2);
    //std::cout << "Serialized Message: " << serializedData2<< std::endl;
    //std::cout << "Deserialized Message: " << deserializedMessage2.GetType() << deserializedMessage2.getPath() << std::endl;
    MusicPlayer player;
    MessageInterpreter interpreter(&player);
    Connection connectionSubordinate(55555, L"127.0.0.1",&interpreter);
    connectionSubordinate.init();
    connectionSubordinate.startListening();
    

	return 0;


    
}
