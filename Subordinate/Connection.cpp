#include "Connection.h"

Connection::Connection(int port, LPCWSTR ipAddress, MessageInterpreter* interpreter)
{
    _interpreter = interpreter;
	_port = port;
    _ipAddress = ipAddress;
    
}

int Connection::init()
{
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        std::cout << "The Winsock dll not found" <<std::endl;
        return 0;
    }
    else
    {
        std::cout << "The Winsock dll found!" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    _clientSocket = INVALID_SOCKET;
    _clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_clientSocket == INVALID_SOCKET)
    {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "Socket() is OK!" << std::endl;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _ipAddress, &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(_port);
    if (connect(_clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        std::cout << "Client:connect() failed" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }
    else
    {
        std::cout << "Client:connect() is OK!" << std::endl;
        std::cout << "Client can start sending and reciving data" << std::endl;
    }
    
}

void Connection::startListening()
{
    const int bufferSize = 2024;
    char buffer[bufferSize];
    int bytesReceived;

    

    // Receive data from the server
    while (true) 
    {
        // Clear the buffer
        memset(buffer, 0, bufferSize);

        bytesReceived = recv(_clientSocket, buffer, bufferSize - 1, 0);
        
        if (bytesReceived == SOCKET_ERROR) {
            int errorCode = WSAGetLastError();
            if (errorCode == WSAECONNRESET) {
                std::cerr << "Connection reset by peer (Error code: " << errorCode << ")." << std::endl;
            }
            else {
                std::cerr << "Receive failed: " << errorCode << std::endl;
            }

        }

        // Check for connection closure
        if (bytesReceived == 0) {
            std::cerr << "Connection closed by server." << std::endl;

        }

        // Construct a std::string from the buffer and the number of bytes received
        //std::cout<< std::string(buffer, bytesReceived);
        std::string data(buffer, bytesReceived);
        _interpreter->interpretAndExecute(data);
    }
}

void Connection::uninit()
{
    // Shutdown the connection since no more data will be sent
    if (_clientSocket != INVALID_SOCKET)
    {
        int result = shutdown(_clientSocket, SD_BOTH);
        if (result == SOCKET_ERROR) {
            std::cout << "shutdown failed: " << WSAGetLastError() << std::endl;
            closesocket(_clientSocket);  // Always ensure the socket is closed
            WSACleanup();
            return;
        }

        // Close the socket
        closesocket(_clientSocket);
        std::cout << "Socket closed successfully." << std::endl;
    }

    // Clean up Winsock
    WSACleanup();
    std::cout << "Winsock cleanup done." << std::endl;
}




