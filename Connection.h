
//conexiune(55555, L"127.0.0.1");
#include <iostream>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include<cstring>
#include"MusicPlayer.h"

class Connection {
public:
    Connection(int port, LPCWSTR ipAddress,MusicPlayer player);
    int init();
    void socketAccept();
    void Send(const std::string message);
    void uninit();
private:
    SOCKET _serverSocket;
    SOCKET _acceptSocket;
    LPCWSTR _ipAddress;
    MusicPlayer _player;
    int _port;
};


