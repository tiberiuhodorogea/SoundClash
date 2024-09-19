
//conexiune(55555, L"127.0.0.1");
#include <iostream>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include<cstring>
#include"MessageInterpreter.h"
class Connection {
public:
    Connection(int port, LPCWSTR ipAddress, MessageInterpreter* interpreter);
    int init();
    void startListening();
    void uninit();
private:
    MessageInterpreter* _interpreter;
    LPCWSTR _ipAddress;
    SOCKET _clientSocket;
    SOCKET _acceptSocket;
    int _port;
    
};


